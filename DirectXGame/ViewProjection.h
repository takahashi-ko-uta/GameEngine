#pragma once
#include "WinApp.h"
#include <DirectXMath.h>
#include <wrl.h>
#include <d3d12.h>
#include "Vector3.h"
#include "Matrix4.h"

class ViewProjection
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

private:

	struct ConstBufferDataViewProjection
	{
		Matrix4 view;
		Matrix4 projection;
		Matrix4 viewProjection;
		Vector3 cameraPos;
	};

	Matrix4 matView_;
	Matrix4 matProjection_;
	Matrix4 matViewProjection_;

public:
	void Initialize();
	void Update();

	Matrix4 GetViewProjectionMatrix() const { return matViewProjection_; }


	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff_;
	//�}�b�s���O
	ConstBufferDataViewProjection* constMap_;

	Vector3 eye = { 0.0f, 0.0f, -50.0f };
	Vector3 target;
	Vector3 up = { 0.0f,1.0f,0.0f };

	int fovAngleY = 45;

	// �A�X�y�N�g��
	float aspectRatio = WinApp::window_width / WinApp::window_height;
	//�j�A�N���b�v(��O���̐[�x���E)
	float nearZ = 0.1f;
	//�t�@�[�N���b�v(�����̐[�x���E)
	float farZ = 1000.0f;
};