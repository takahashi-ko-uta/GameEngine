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

	//�P�ʍs������߂�
	static Matrix4 Identity();
	//�g��k���s��̐ݒ�
	static Matrix4 Scale(const Vector3& s);
	//��]�s��̐ݒ�
	static Matrix4 Rotate(Vector3 rot);
	static Matrix4 RotateX(float angle);
	static Matrix4 RotateY(float angle);
	static Matrix4 RotateZ(float angle);
	//���s�ړ��s��̐ݒ�
	static Matrix4 Translate(const Vector3& t);
	//���W�ϊ�(�x�N�g���ƍs��̊|���Z)
	static Vector3 Transform(const Vector3& v, const Matrix4& m);
};
//������Z�q�I�[�o�[���[�h
Matrix4& operator*=(Matrix4& m1, const Matrix4& m2);
//2�����Z�q�I�[�o�[���[�h
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Vector3 operator*(const Vector3& v, const Matrix4& m);