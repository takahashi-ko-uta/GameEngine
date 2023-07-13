#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Audio.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionPrimitive.h"
#include "ParticleManager.h"

struct DrawObject
{
	float m_PosX;		// 描画座標X
	float m_PosY;		// 描画座標Y
	float m_Radius;		// 半径(描画用)
	float m_CenterX;	// 中心座標X
	float m_CenterY;	// 中心座標Y
	float m_Angle;		// 角度
	float m_Length;		// 半径の長さ
};

class GamePlayScene
{
public://メンバ関数
	//初期化
	void Initialize(DirectXCommon* dxCommon, Input* input);
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	//描画
	void Draw();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Camera* camera_ = nullptr;
	//スプライト共通部の生成
	SpriteCommon* spriteCommon_ = nullptr;
	//スプライト生成
	Sprite* sprite1_ = nullptr;
	Sprite* sprite2_ = nullptr;
	//パーティクル生成
	ParticleManager* particle1_ = nullptr;
	ParticleManager* particle2_ = nullptr;
	//モデル生成
	Model* modelGround1_ = nullptr;
	Model* modelGround2_ = nullptr;
	Model* modelSphere_ = nullptr;
	//3Dオブジェクト生成
	Object3d* objGround_[5][5] = {};
	Object3d* objSphere_ = nullptr;
	//当たり判定
	Sphere sphere;
	Plane plane;
	Ray ray;
	//audio生成
	Audio* audio_ = nullptr;
	XMFLOAT3 cameraEye = { 0,0,0 };

	//回転運動
	DrawObject rotObj =
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

