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
#include "SoldierRoute.h"
#include "SearchRoute.h"
#include "Enemy.h"
#include "Solder.h"

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
	//兵隊のルート検索
	//SoldierRoute* soldierRoute_[4];
	XMFLOAT3 soldiersPos_[4];//各兵隊の位置
	XMINT2 startFloor[4];
	XMINT2 goalFloor[4];
	XMFLOAT3 floorPos[11][11];
	int costMap[11][11];

	//兵隊
	Solider* solider_[4];
	XMFLOAT3 soldiersPos_[36];//兵隊全員の位置
	bool isSoldiersLife_[36]; //兵隊全員の生存フラグ

	//敵
	Enemy* enemy_ = nullptr;
	XMINT2 houseFloor_[3];

};

