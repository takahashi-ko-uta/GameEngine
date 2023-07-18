#pragma once
#include <DirectXMath.h>
#include <wrl.h>
#include <d3d12.h>

struct ViewProjection
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public://�\���́A�o�b�t�@
	struct ConstBufferDataViewProjection
	{
		XMMATRIX view;
		XMMATRIX projection;
		XMFLOAT3 cameraPos;
	};
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff_;
	//�}�b�s���O
	ConstBufferDataViewProjection* constMap_;

public://�֐�
	//������
	void Initialize();
	//�萔�o�b�t�@����
	void CreateConstBuffer();
	//�}�b�s���O
	void MapingCB();
	//�X�V
	void Update();

	//�e�s��X�V
	void UpdateView();
	void UpdateProjection();

	//�]��
	void Trans();

public://�ϐ�
	//���_
	XMFLOAT3 eye_;
	//�����_
	XMFLOAT3 target_;
	//������x�N�g��
	XMFLOAT3 up_;

	//����p
	float angle_ = 0.0f;
	//�A�X�y�N�g��
	float aspect_ = 0.0f;
	//�j�A�N���b�v(��O���̐[�x���E)
	float nearZ_ = 0.0f;
	//�t�@�[�N���b�v(�����̐[�x���E)
	float farZ_ = 0.0f;

	//�r���[�s��
	XMMATRIX matView_;
	//�v���W�F�N�V�����s��
	XMMATRIX matProjection_;
	//�r���[�v���W�F�N�V�����s��(�����p)
	XMMATRIX matViewProjection_;
	//�r���{�[�h�s��
	XMMATRIX matBillboard_;
	//Y�����r���{�[�h�s��
	XMMATRIX matBillboardY_;

};