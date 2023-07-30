#pragma once
#include "Camera.h"
#include "DirectXCommon.h"
#include "Input.h"

struct RotateObject
{
	float m_PosX;		// 描画座標X
	float m_PosY;		// 描画座標Y
	float m_Radius;		// 半径(描画用)
	float m_CenterX;	// 中心座標X
	float m_CenterY;	// 中心座標Y
	float m_Angle;		// 角度
	float m_Length;		// 半径の長さ
};

class GameCamera
{
public://メンバ関数
	//初期化
	void Initialize(Camera* camera);
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();


private://メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Camera* camera_ = nullptr;

	//回転運動
	RotateObject rotObj =
	{
		0,		//描画座標X
		0,		//描画座標Y
		10,		//半径(描画用)
		0,		//中心座標X
		0,		//中心座標Y
		0.0f,	//角度
		50.0f,	//半径の長さ
	};

	// 度数法の角度を弧度法に変換
	float radius = rotObj.m_Angle * 3.14f / 180.0f;

	// 三角関数を使用し、円の位置を割り出す。
	float add_x = cos(radius) * rotObj.m_Length;
	float add_y = sin(radius) * rotObj.m_Length;
};

