#include "Vector3Math.h"
#include <math.h>

namespace Vector3Math
{
	//•ÏŠ·—p
	DirectX::XMFLOAT3 ConvertVector3(const Vector3& vec3)
	{
		return DirectX::XMFLOAT3(vec3.x, vec3.y, vec3.z);
	}

	Matrix4 ConvertMatrix4(const DirectX::XMMATRIX& mat)
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


	Vector3 diff(Vector3& vecA, Vector3& vecB)
	{
		Vector3 vecC;
		vecC.x = vecA.x - vecB.x;
		vecC.y = vecA.y - vecB.y;
		vecC.z = vecA.z - vecB.z;

		return vecC;
	}

	bool norm(Vector3& vec3) {
		float norm = sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
		return norm;
	}
	
	Vector3 Normalize(Vector3& vec3)
	{
		float norm = Vector3Math::norm(vec3);
		float mag = 1 / norm;
		vec3.x *= mag;
		vec3.y *= mag;
		vec3.z *= mag;

		return vec3;
	}
}