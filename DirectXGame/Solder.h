#pragma once
#include "Model.h"
#include "Object3d.h"
#include "SoldierRoute.h"

class Normal
{
public:
	//初期化
	void Initialize(int soldierNum, int normalNum);
	//終了
	void Finalize();
	//毎フレーム処理
	void Update(XMFLOAT3 pos);
	//描画
	void Draw();

	//getter
	XMFLOAT3 GetPosition() { return obj_->GetPosition(); }
	bool GetIsLife() { return isLife; }
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	int normalNum_;
	XMFLOAT3 leaderPos;//指定されている床の座標
	XMFLOAT3 goalPos;//目的地
	bool isLife = true; //生存フラグ
	int32_t life = 3;	//体力
};


class Leader
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

	//getter
	XMFLOAT3 GetPosition() { return obj_->GetPosition(); }
	bool GetIsLife() { return isLife; }
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	XMFLOAT3 floorPos;//指定されている床の座標

	bool isLife = true; //生存フラグ
	int32_t life = 3;	//体力

};


class Solider
{
public:
	//初期化
	void Initialize(XMFLOAT3 spawnPos, int soldierNum);
	//終了
	void Finalize();
	//毎フレーム処理
	void Update(XMINT2 startFloor, XMINT2 goalFloor, XMFLOAT3 floorPos[11][11],int selectSoldier, int costMap[11][11]);
	//描画
	void Draw();

	//getter
	XMFLOAT3 GetSoldierRoutePos() { return soldierRoute_->GetPosition(); }
	//兵隊全員の位置と生存フラグを取得できる
	void GetSoldiersStatus();
private:
	SoldierRoute* soldierRoute_ = nullptr;
	Leader* leader = nullptr;
	Normal* normal[8];

	XMFLOAT3 soldiersPos[9];//兵隊全員の位置
	bool isSoldiersLife[9]; //兵隊全員の生存フラグ
};