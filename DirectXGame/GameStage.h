#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Input.h"

class GameStage
{
public://メンバ関数
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	void Select();
	void SetSoldiersFloor();//兵隊のいる床を取得
	void ChangeFloorColor();
	//描画
	void Draw();

	//getter
	const XMFLOAT3 GetSpawnFloor(int num);
	void GetMapData(int mapData[11][11], int mapSizeX, int mapSizeY);
	void GetFloorPos(XMFLOAT3 floorPos[11][11]);
	void GetStartPos(XMINT2 startFloor[4]);
	void GetGoalPos(XMINT2 goalFloor[4]);

	//setter
	void SetSoldiersPos(XMFLOAT3 soldiersPos[4]);
private://メンバ変数
	Input* input = nullptr;
	Model* modelGround1_ = nullptr;
	Model* modelGround2_ = nullptr;
	//ステージの幅
	const static int mapSize = 11;//真ん中があるといいので奇数

	int map[3];

	int32_t MapData[mapSize][mapSize] = {
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1
	};


	Object3d* objFloor_[mapSize][mapSize] = {};
	XMFLOAT3 floorPos[11][11];

	XMINT2 selectFloor;
	bool IsGoal = false;//goalFloorに保存するか否か
	int selectSoldier = 5;//何も選択してないときは5
	XMINT2 startFloor[4];
	XMINT2 goalFloor[4];
	  
	XMINT2 spawnFloor[4];
	XMFLOAT3 soldiersPos[4];//各兵隊の位置

	XMINT2 soldiersFloor[4];
};

