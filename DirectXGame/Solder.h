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

private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	int normalNum_;
	XMFLOAT3 leaderPos;//指定されている床の座標
	XMFLOAT3 goalPos;//目的地

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
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	XMFLOAT3 floorPos;//指定されている床の座標

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
private:
	SoldierRoute* soldierRoute_ = nullptr;
	Leader* leader = nullptr;
	Normal* normal[8];
};