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
#include "Soldier.h"
#include "SearchRoute.h"
#include "EnemyShip.h"

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

	//兵隊(4部隊)
	Soldier* soldier_[4];
	XMFLOAT3 soldiersPos_[4];//各兵隊の位置
	XMINT2 startFloor[4];
	XMINT2 goalFloor[4];
	XMFLOAT3 floorPos[11][11];

	//敵
	EnemyShip* ENship = nullptr;
};

