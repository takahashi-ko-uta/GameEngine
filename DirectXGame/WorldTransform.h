#pragma once
#include "Matrix4.h"
#include <wrl.h>
#include <d3d12.h>
#include "DirectXCommon.h"

class WorldTransform
{
private:
	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		Matrix4 w; // ワールド行列
	};

	DirectXCommon* dxCommon_ = nullptr;
	ConstBufferData* constMap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer;
public:
	
	Matrix4 matWorld;
	Vector3 scale = { 1,1,1 };
	Vector3 rotation;
	Vector3 translation;
	WorldTransform* parent = nullptr;
	
	void Initialize();
	void Update();
	Vector3 GetWorldScale() { return { matWorld.m[0][0],matWorld.m[1][1],matWorld.m[2][2] }; }
	Vector3 GetWorldPosition() { return { matWorld.m[3][0],matWorld.m[3][1],matWorld.m[3][2] }; }
	//Vector3 GetWorldRotation() { return { matWorld.m[3][0],matWorld.m[3][1],matWorld.m[3][2] }; }
};