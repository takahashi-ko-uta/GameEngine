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

	//単位行列を求める
	static Matrix4 Identity();
	//拡大縮小行列の設定
	static Matrix4 Scale(const Vector3& s);
	//回転行列の設定
	static Matrix4 Rotate(Vector3 rot);
	static Matrix4 RotateX(float angle);
	static Matrix4 RotateY(float angle);
	static Matrix4 RotateZ(float angle);
	//平行移動行列の設定
	static Matrix4 Translate(const Vector3& t);
	//座標変換(ベクトルと行列の掛け算)
	static Vector3 Transform(const Vector3& v, const Matrix4& m);
};
//代入演算子オーバーロード
Matrix4& operator*=(Matrix4& m1, const Matrix4& m2);
//2項演算子オーバーロード
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Vector3 operator*(const Vector3& v, const Matrix4& m);