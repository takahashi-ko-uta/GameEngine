#pragma once
#include "Input.h"
#include "Model.h"
#include "Object3d.h"

class EnemyShip
{
public:
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update(XMFLOAT3 floorPos[11][11]);
	//船のゴールを決める
	void CreateGoal(XMFLOAT3 floorPos[11][11]);
	//船が出現してから着陸するまでの動き
	void Move();
	//描画
	void Draw();
private:
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	int32_t direction = 0;
	int32_t floorNum = 0;
	int num;
	bool isSpawn = true;  //スポーンに必要な値を決める
	bool isSelect = false;//ゴール位置を決める
	bool isMove = false;  //着陸まで動く
	XMINT2 goalFloor;
	XMFLOAT3 startPos;
	XMFLOAT3 goalPos;
	XMFLOAT3 floorPos_[11][11];
	float randomPos;//スタート位置をランダムにする
};

