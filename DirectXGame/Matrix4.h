#pragma once
#include "Vector3.h"

class Matrix4
{
public:
	float m[4][4] =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	//�P�ʍs��
	static Matrix4 Identity();
	//
	static Matrix4 Zero();
	//�r���[�|�[�g�s��
	static Matrix4 CreateViewport(float w, float h, Vector3 offset);
	//�g��k���s��
	static Matrix4 Scale(const Vector3& s);
	//��]�s��
	static Matrix4 Rotate(Vector3 rot);
	static Matrix4 RotateX(float angle);
	static Matrix4 RotateY(float angle);
	static Matrix4 RotateZ(float angle);
	//���s�ړ��s��
	static Matrix4 Translate(const Vector3& t);
	//�x�N�g���ƍs��̊|���Z
	static Vector3 Vector3Mat(const Vector3& v, const Matrix4& m);
	//�x�N�g���ƍs��̊|����w���Z
	static Vector3 MatZdivision(const Vector3& v, const Matrix4& m);
};


//������Z�q�I�[�o�[���[�h
Matrix4& operator*=(Matrix4& m1, const Matrix4& m2);
//2�����Z�q�I�[�o�[���[�h
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Vector3 operator*(const Vector3& v, const Matrix4& m);