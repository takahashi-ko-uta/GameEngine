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
	//3Dオブジェクト生成
	Object3d* objGround_ = nullptr;
	//当たり判定
	Sphere sphere;
	Plane plane;
	Ray ray;
	//audio生成
	Audio* audio_ = nullptr;
	XMFLOAT3 cameraEye = { 0,0,0 };
};

