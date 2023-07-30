#include "WorldTransform.h"
#include "DirectXCommon.h"
#include <d3dx12.h>

void WorldTransform::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();

	// �o�b�t�@�̐���
	HRESULT result = dxCommon_->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&constBuffer));

	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	result = (*constBuffer.GetAddressOf())->Map(0, nullptr, (void**)constMap);
	// �q���������
	(*constBuffer.GetAddressOf())->Unmap(0, nullptr);
}

void WorldTransform::Update()
{
	Matrix4 matScale = Matrix4::Scale(scale);
	Matrix4 matRot = Matrix4::Rotate(rotation);
	Matrix4 matTrans = Matrix4::Translate(translation);
	matWorld = matScale * matRot * matTrans;
	//�e�q�֌W����������ǉ�
	if (parent) { matWorld *= parent->matWorld; }

	constMap->world = matWorld;
}
