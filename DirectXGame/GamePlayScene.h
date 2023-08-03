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

#include "GameCamera.h"
#include "GameSprite.h"
#include "GameStage.h"
#include "Player.h"

class GamePlayScene
{
public://メンバ関数
	//初期化
	void Initialize();
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
	
	//パーティクル生成
	ParticleManager* particle1_ = nullptr;
	ParticleManager* particle2_ = nullptr;
	//モデル生成
	Model* modelSphere_ = nullptr;
	//3Dオブジェクト生成
	Object3d* objSphere_ = nullptr;
	//当たり判定
	Sphere sphere;
	Plane plane;
	Ray ray;
	//audio生成
	Audio* audio_ = nullptr;

	//ゲーム用カメラ
	GameCamera* gameCamera_ = nullptr;
	//ゲームに使うスプライト
	GameSprite* gameSprite_ = nullptr;
	//ステージ
	GameStage* gameStage_ = nullptr;
	//Player
	Player* player_ = nullptr;
};

