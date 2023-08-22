#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Input.h"

class GameStage
{
public://�����o�֐�
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	void Select();
	void SetStartGoal();
	void SetSoldiersFloor();//�����̂��鏰���擾
	void ChangeFloorColor();
	void CreateCostMap(int mapData[11][11]);
	//�`��
	void Draw();

	//getter
	const XMFLOAT3 GetSpawnPos(int num);
	void GetFloorPos(XMFLOAT3 floorPos[11][11]);
	void GetStartPos(XMINT2 startFloor[4]);
	void GetGoalPos(XMINT2 goalFloor[4]);
	int GetSelectSoldier() { return selectSoldier; }

	//setter
	void SetSoldiersPos(XMFLOAT3 soldiersPos[4]);

	
private://�����o�ϐ�
	Input* input = nullptr;
	
	//�X�e�[�W�̕�
	const static int mapSize = 11;//�^�񒆂�����Ƃ����̂Ŋ

	int32_t MapData[mapSize][mapSize] = {//1 = ���@2 = 2�K�@3 = �K�i 4 = ��
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1,40, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,41, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,42, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	Model* modelGround1_ = nullptr;
	Model* modelGround2_ = nullptr;
	Model* modelSea_ = nullptr;
	Model* modelHouse_ = nullptr;
	Object3d* objFloor_[mapSize][mapSize] = {};
	Object3d* objSea_ = nullptr;
	Object3d* objHouse_[3];//3��
	XMFLOAT3 floorPos[11][11];

	XMINT2 selectFloor;
	bool IsGoal = false;//goalFloor�ɕۑ����邩�ۂ�
	int selectSoldier = 5;//�����I�����ĂȂ��Ƃ���5
	XMINT2 startFloor[4];
	XMINT2 goalFloor[4];
	  
	XMINT2 spawnFloor[4];
	XMFLOAT3 soldiersPos[4];//�e�����̈ʒu

	XMINT2 soldiersFloor[4];
};

