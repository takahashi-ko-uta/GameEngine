#include "Matrix4.h"
#include"Vector3.h"
#include<cmath>

Matrix4 Matrix4::Identity()
{
	Matrix4 result
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return result;
}

Matrix4 Matrix4::Zero()
{
	Matrix4 result
	{
		0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f
	};

	return result;
}

Matrix4 Matrix4::CreateViewport(float w, float h, Vector3 offset)
{
	Matrix4 result
	{
		          w/2,         0.0f, 0.0f, 0.0f,
		         0.0f,	       -h/2, 0.0f, 0.0f,
		         0.0f,	       0.0f, 1.0f, 0.0f,
		w/2+offset.x , h/2+offset.y, 0.0f, 1.0f
	};

	return result;
}

Matrix4 Matrix4::Scale(const Vector3& s)
{
	Matrix4 result
	{
		s.x,0.0f,0.0f,0.0f,
		0.0f,s.y,0.0f,0.0f,
		0.0f,0.0f,s.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}

Matrix4 Matrix4::Rotate(Vector3 rot)
{
	return RotateZ(rot.z) * RotateX(rot.x) * RotateY(rot.y);
}

Matrix4 Matrix4::RotateX(float angle)
{
	float sin = std::sin(angle);
	float cos = std::cos(angle);

	Matrix4 result
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,cos ,sin ,0.0f,
		0.0f,-sin,cos,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}

Matrix4 Matrix4::RotateY(float angle)
{
	float sin = std::sin(angle);
	float cos = std::cos(angle);

	Matrix4 result
	{
		cos,0.0f,-sin,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		sin,0.0f,cos,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}

Matrix4 Matrix4::RotateZ(float angle)
{
	float sin = std::sin(angle);
	float cos = std::cos(angle);

	Matrix4 result
	{
		cos,sin,0.0f,0.0f,
		-sin,cos,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}

Matrix4 Matrix4::Translate(const Vector3& t)
{
	Matrix4 result
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		t.x ,t.y ,t.z ,1.0f
	};

	return result;
}

Vector3 Matrix4::Vector3Mat(const Vector3& v, const Matrix4& m)
{
	Vector3 vec3;

	vec3.x = (v.x * m.m[0][0]) +
		(v.y * m.m[1][0]) +
		(v.z * m.m[2][0]) +
		(0 * m.m[3][0]);

	vec3.y = (v.x * m.m[0][1]) +
		(v.y * m.m[1][1]) +
		(v.z * m.m[2][1]) +
		(0 * m.m[3][1]);

	vec3.z = (v.x * m.m[0][2]) +
		(v.y * m.m[1][2]) +
		(v.z * m.m[2][2]) +
		(0 * m.m[3][2]);

	return vec3;
}

Vector3 Matrix4::MatZdivision(const Vector3& v, const Matrix4& m)
{
	Vector3 vec3;
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];

	vec3.x = (v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0]) / w;
	vec3.y = (v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1]) / w;
	vec3.z = (v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]) / w;

	return vec3;
}

Matrix4& operator*=(Matrix4& m1, const Matrix4& m2)
{
	Matrix4 result{ 0 };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += (m1.m[i][k] * m2.m[k][j]);
			}
		}
	}
	m1 = result;

	return m1;
}

Matrix4 operator*(const Matrix4& m1, const Matrix4& m2)
{
	Matrix4 result = m1;

	return result *= m2;
}

Vector3 operator*(const Vector3& v, const Matrix4& m)
{
	return Matrix4::Vector3Mat(v, m);
}
