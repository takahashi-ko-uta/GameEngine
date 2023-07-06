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
	Sprite* sprite_ = nullptr;
	//モデル生成
	Model* model_ = nullptr;
	Model* modelCube_ = nullptr;
	Model* modelSphere = nullptr;
	Model* modelPlane_ = nullptr;
	//3Dオブジェクト生成
	Object3d* objCube_ = nullptr;
	Object3d* objSphere_ = nullptr;
	Object3d* objPlane_ = nullptr;
	//当たり判定
	Sphere sphere;
	Plane plane;
	Ray ray;
	//audio生成
	Audio* audio_ = nullptr;
	XMFLOAT3 cameraEye = { 0,0,0 };
};

