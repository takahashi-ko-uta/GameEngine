#pragma once
#include "EnemyShip.h"
#include "SoldierRoute.h"

class Enemy
{
public:
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update(XMFLOAT3 pos, XMINT2 goal, bool isGoal, XMFLOAT3 floorPos[11][11], XMINT2 houseFloor[3]);
	//一番近い家を見つける
	void SearchHouse(XMINT2 houseFloor[3]);
	//船に乗ってるとき
	void OnShip(bool isGoal);
	//着陸する
	void Landing(XMINT2 goal);
	//描画
	void Draw();

	//getter
	XMFLOAT3 GetPosition() { return obj_->GetPosition(); }
	XMINT2 GetNowFloor() { return nowFloor; }
	XMINT2 GetGoalFloor() { return goalFloor; }
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	XMFLOAT3 floorPos_[11][11];//床の座標
	XMFLOAT3 shipPos_;
	bool isLanding = false;
	XMINT2 nowFloor;	//今いる床
	XMINT2 goalFloor;

};

class EnemySoldier
{
public:
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update(XMFLOAT3 floorPos[11][11], XMINT2 houseFloor[3], int costMap[11][11]);
	//描画
	void Draw();
private:
	EnemyShip* ship_ = nullptr;
	Enemy* enemy_ = nullptr;
	SoldierRoute* soldierRoute_ = nullptr;
};
