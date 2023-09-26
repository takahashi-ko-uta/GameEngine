#pragma once
#include "EnemyShip.h"
#include "SoldierRoute.h"

class EnemyNormal
{
public:
	//初期化
	void Initialize(int soldierNum);
	//終了
	void Finalize();
	//毎フレーム処理
	void Update(XMFLOAT3 pos);
	//描画
	void Draw();

private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	int soldierNum_;
	XMFLOAT3 leaderPos;//指定されている床の座標
	XMFLOAT3 goalPos;//目的地

};

class EnemyLeader
{
public:
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update(XMFLOAT3 pos, XMINT2 goal, bool isGoal, XMFLOAT3 floorPos[11][11], int costMap[11][11], XMINT2 houseFloor[3]);
	void CreateRoute();
	//一番近い家を見つける
	void SearchHouse();
	//船に乗ってるとき
	void OnShip(bool isGoal);
	//着陸する
	void Landing(XMINT2 goal);
	//家の近くまで動く
	void Move(XMINT2 houseFloor[3]);
	//2点間の距離を求める
	float Distance(float p1X, float p1Y, float p2X, float p2Y);
	//描画
	void Draw();

	//getter
	XMFLOAT3 GetPosition() { return obj_->GetPosition(); }
	XMINT2 GetNowFloor() { return nowFloor; }
	XMINT2 GetGoalFloor() { return goalFloor; }
	bool GetIsMove() { return isMove; }
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;
	SearchRoute* enemyRoute_ = nullptr;
	XMFLOAT3 floorPos_[11][11];//床の座標
	XMFLOAT3 shipPos_;
	bool isChangeMap = true;
	bool isOnShip = true;
	bool isLanding = false;
	bool isMove = false;
	XMINT2 nowFloor;	//今いる床
	int32_t goalHouseNum;
	XMINT2 goalFloor;
	XMINT2 houseFloor_[3];
	XMFLOAT3 housePos[3];
	SearchRoute::Cell start_ = SearchRoute::Cell(0, 0);
	SearchRoute::Cell goal_ = SearchRoute::Cell(0, 0);
	int costMap_[11][11];
	XMINT2 route[40];
	int32_t routeNum_ = 0;

	int aaaa = 0;
};

//敵のひとかたまり
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

	//setter
	void SetIsStart(bool isStart) { this->isStart_ = isStart; }
private:
	EnemyShip* ship_ = nullptr;
	EnemyLeader* leader_ = nullptr;
	EnemyNormal* normal_[8];//最大8人する
	int32_t enemyNum;//敵(normal)の数
	bool isStart_;
};

class Enemy
{
public:
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update(XMFLOAT3 floorPos[11][11], XMINT2 houseFloor[3], int costMap[11][11]);
	//スポーン
	void Spawn();
	//描画
	void Draw();

private:
	EnemySoldier* soldier[5];
	bool isStartShip[5];
	int32_t spawnTime;
	int32_t num;
	bool isSpawn = true;
	bool isDelete = false;
	int32_t enemyNum;//敵(normal)の数
};

