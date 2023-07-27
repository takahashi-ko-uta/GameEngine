#pragma once
#include "Matrix4.h"
#include <wrl.h>
#include <d3d12.h>
#include "DirectXCommon.h"

class WorldTransform
{
private:
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		Matrix4 world; // ���[���h�s��
	};

public:
	DirectXCommon* dxCommon_ = nullptr;
	Matrix4 matWorld;
	Vector3 scale = { 1,1,1 };
	Vector3 rotation;
	Vector3 translation;
	WorldTransform* parent = nullptr;
	ConstBufferData* constMap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer;


	void Initialize(DirectXCommon* dxCommon);
	void Update();
	Vector3 GetWorldPosition() { return { matWorld.m[3][0],matWorld.m[3][1],matWorld.m[3][2] }; }
};