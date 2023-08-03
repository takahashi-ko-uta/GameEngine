#include "ViewProjection.h"
#include <cassert>
#include <cmath>
#include "WinApp.h"
#include "DirectXCommon.h"
#include "D3D12Common.h"

using namespace DirectX;

//変換用
XMFLOAT3 ConvertVector3(const Vector3& vec3)
{
	return XMFLOAT3(vec3.x, vec3.y, vec3.z);
}

Matrix4 ConvertMatrix4(const XMMATRIX& mat)
{
	Matrix4 mat4;

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++)
		{
			mat4.m[i][j] = mat.r[i].m128_f32[j];
		}
	}

	return mat4;
}

void ViewProjection::Initialize()
{
	CreateBuffer(constBuff_.GetAddressOf(), &constMap_, (sizeof(ConstBufferDataViewProjection) + 0xff) & ~0xff);
}




void ViewProjection::Update()
{
	// プロジェクション行列を求める
	matProjection_ = Matrix4::Zero();
	matProjection_.m[0][0] = 1.0f / (aspectRatio * std::tan(fovAngleY / 2.0f));
	matProjection_.m[1][1] = 1.0f / std::tan(fovAngleY / 2.0f);
	matProjection_.m[2][2] = farZ / (farZ - nearZ);
	matProjection_.m[2][3] = 1.0f;
	matProjection_.m[3][2] = -nearZ * farZ / (farZ - nearZ);

	// ビュー行列を求める
	matView_ = ConvertMatrix4(XMMatrixLookAtLH(XMLoadFloat3(&ConvertVector3(eye)), XMLoadFloat3(&ConvertVector3(target)), XMLoadFloat3(&ConvertVector3(up))));

	constMap_->viewProjection = GetViewProjectionMatrix();
	constMap_->cameraPos = eye;

	matViewProjection_ = matView_ * matProjection_;
}



