#include "ViewProjection.h"
#include <cassert>
#include <cmath>
#include "WinApp.h"
#include "DirectXCommon.h"

using namespace DirectX;

void ViewProjection::Initialize()
{
	//�x�N�g��
	eye_ = { 0.0f, 0.0f, -100.0f };
	target_ = { 0.0f, 0.0f, 0.0f };
	up_ = { 0.0f,1.0f,0.0f };

	//����p
	angle_ = XMConvertToRadians(45.0f);
	//�A�X�y�N�g��
	aspect_ = (float)WinApp::window_width / WinApp::window_height;
	//�j�A�N���b�v
	nearZ_ = 0.1f;
	//�t�@�[�N���b�v
	farZ_ = 1000.0f;

	//�s��
	matView_ = XMMatrixIdentity();
	matProjection_ = XMMatrixIdentity();
	matBillboard_ = XMMatrixIdentity();
	matBillboardY_ = XMMatrixIdentity();

	//�萔�o�b�t�@����
	CreateConstBuffer();
	//�}�b�s���O
	MapingCB();
	//�X�V
	Update();
	//�]��
	Trans();
}

void ViewProjection::CreateConstBuffer()
{
	HRESULT result;

	D3D12_HEAP_PROPERTIES cbHeapProp{};		//�q�[�v�ݒ�
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD; //GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbResourseDesc{};
	cbResourseDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourseDesc.Width = (sizeof(ConstBufferDataViewProjection) + 0xff) & ~0xff;//256�o�C�g�A���C�������g
	cbResourseDesc.Height = 1;
	cbResourseDesc.DepthOrArraySize = 1;
	cbResourseDesc.MipLevels = 1;
	cbResourseDesc.SampleDesc.Count = 1;
	cbResourseDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�萔�o�b�t�@�̐���
	result = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&cbHeapProp,//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&cbResourseDesc, //���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));
}

void ViewProjection::MapingCB()
{
	HRESULT result;

	result = constBuff_->Map(0, nullptr, (void**)&constMap_);
	assert(SUCCEEDED(result));
}

void ViewProjection::Update()
{
	//�s��v�Z
	UpdateView();
	UpdateProjection();

	//����
	matViewProjection_ = matView_ * matProjection_;
}

void ViewProjection::UpdateView()
{
	//���_���W
	XMVECTOR eyePos = XMLoadFloat3(&eye_);
	//�����_���W
	XMVECTOR targetPos = XMLoadFloat3(&target_);
	//������x�N�g��
	XMVECTOR upVec = XMLoadFloat3(&up_);

	//�J����Z��(����)
	XMVECTOR axisZ = XMVectorSubtract(targetPos, eyePos);

	assert(!XMVector3Equal(axisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(axisZ));
	assert(!XMVector3Equal(upVec, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVec));
	//���K��
	axisZ = XMVector3Normalize(axisZ);

	//X��(�E)
	XMVECTOR axisX;
	//X���͏������Z���̊O�ςŌ��܂�
	axisX = XMVector3Cross(upVec, axisZ);
	//���K��
	axisX = XMVector3Normalize(axisX);

	//Y��(�����)
	XMVECTOR axisY;
	//Y����Z����X���̊O�ςŌ��܂�
	axisY = XMVector3Cross(axisZ, axisX);

	//�J������]�s��
	XMMATRIX matCameraRot;
	//�J�������W�����[���h���W�n�̕ϊ��s��
	matCameraRot.r[0] = axisX;
	matCameraRot.r[1] = axisY;
	matCameraRot.r[2] = axisZ;
	matCameraRot.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	//�]�u���ċt�s����v�Z
	matView_ = XMMatrixTranspose(matCameraRot);

	//���_���W * -1
	XMVECTOR reverseEyePos = XMVectorNegate(eyePos);
	//�J�����̈ʒu���烏�[���h���_�ւ̃x�N�g��
	XMVECTOR tX = XMVector3Dot(axisX, reverseEyePos);
	XMVECTOR tY = XMVector3Dot(axisY, reverseEyePos);
	XMVECTOR tZ = XMVector3Dot(axisZ, reverseEyePos);
	//��̃x�N�g���ɂ܂Ƃ߂�
	XMVECTOR trans = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
	//�r���[�s��ɕ��s�ړ��������w��
	matView_.r[3] = trans;

	//�S�����r���{�[�h�v�Z
	matBillboard_.r[0] = axisX;
	matBillboard_.r[1] = axisY;
	matBillboard_.r[2] = axisZ;
	matBillboard_.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

	//Y�����r���{�[�h�v�Z
	XMVECTOR yBillAxisX, yBillAxisY, yBillAxisZ;

	//X���͋���
	yBillAxisX = axisX;
	//Y���̓��[���h���W�n��Y��
	yBillAxisY = XMVector3Normalize(upVec);
	//Z����X��Y���̊O�ςŌ��܂�
	yBillAxisZ = XMVector3Cross(yBillAxisX, yBillAxisY);

	matBillboardY_.r[0] = yBillAxisX;
	matBillboardY_.r[1] = yBillAxisY;
	matBillboardY_.r[2] = yBillAxisZ;
	matBillboardY_.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
}

void ViewProjection::UpdateProjection()
{
	//�������e�ɂ��ˉe�s��
	matProjection_ = XMMatrixPerspectiveFovLH(
		angle_, aspect_, nearZ_, farZ_
	);
}

void ViewProjection::Trans()
{
	//�萔�o�b�t�@�ɏ�������
	constMap_->view = matView_;
	constMap_->projection = matProjection_;
	constMap_->cameraPos = eye_;
}