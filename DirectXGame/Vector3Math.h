#pragma once
#include <math.h>
#include <DirectXMath.h>
#include "WorldTransform.h"

namespace Vector3Math
{
	//•ÏŠ·—p
	DirectX::XMFLOAT3 ConvertVector3(const Vector3& vec3);
	Matrix4 ConvertMatrix4(const DirectX::XMMATRIX& mat);

	Vector3 diff(Vector3& vecA, Vector3& vecB);//·•ª(A - B)
	float norm(Vector3& vec3);//’·‚³‚ğ‹‚ß‚é
	Vector3 Normalize(Vector3 vec3);//³‹K‰»
}