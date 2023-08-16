#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Input.h"
#include "SearchRoute.h"

class Soldier
{
public:
	//初期化
	void Initialize(XMFLOAT3 spawnPos, int soldierNum);
	//終了
	void Finalize();
	//毎フレーム処理
	void Update(XMINT2 startFloor, XMINT2 goalFloor, XMFLOAT3 floorPos[11][11]);
	//移動
	void Move();
	//ルート作成
	void CreateRoute();
	//兵隊の位置を床(XMINT2型)に変更
	void ChangeSoldierFloor();
	//スポーンの位置を床(XMINT2型)に変更
	void ChangeSpawnFloor();

	//描画
	void Draw();

	//getter
	const XMFLOAT3 GetPosition() const { return obj_->GetPosition(); }

private:
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	XMFLOAT3 spawnPos_;	//初期位置
	XMINT2 spawnFloor_;
	XMINT2 startFloor;	//スタート位置
	XMINT2 goalFloor;	//ゴール位置

	SearchRoute* searchRoute_ = nullptr;
	SearchRoute::Cell start_ = SearchRoute::Cell(0, 0);
	SearchRoute::Cell goal_ = SearchRoute::Cell(0, 0);
	XMINT2 route_[40];
	XMFLOAT3 floorPos[11][11];
	XMINT2 soldierFloor;

};

