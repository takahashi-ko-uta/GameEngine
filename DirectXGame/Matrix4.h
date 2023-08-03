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

	//単位行列
	static Matrix4 Identity();
	//
	static Matrix4 Zero();
	//ビューポート行列
	static Matrix4 CreateViewport(float w, float h, Vector3 offset);
	//拡大縮小行列
	static Matrix4 Scale(const Vector3& s);
	//回転行列
	static Matrix4 Rotate(Vector3 rot);
	static Matrix4 RotateX(float angle);
	static Matrix4 RotateY(float angle);
	static Matrix4 RotateZ(float angle);
	//平行移動行列
	static Matrix4 Translate(const Vector3& t);
	//ベクトルと行列の掛け算
	static Vector3 Vector3Mat(const Vector3& v, const Matrix4& m);
	//ベクトルと行列の掛けてw除算
	static Vector3 MatZdivision(const Vector3& v, const Matrix4& m);
};


//代入演算子オーバーロード
Matrix4& operator*=(Matrix4& m1, const Matrix4& m2);
//2項演算子オーバーロード
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Vector3 operator*(const Vector3& v, const Matrix4& m);