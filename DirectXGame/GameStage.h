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
	void SetSoldiersFloor();//�����̂��鏰���擾
	void ChangeFloorColor();
	//�`��
	void Draw();

	//getter
	const XMFLOAT3 GetSpawnFloor(int num);
	//setter
	void SetSoldiersPos(XMFLOAT3 soldiersPos[4]);
private://�����o�ϐ�
	Input* input = nullptr;
	Model* modelGround1_ = nullptr;
	Model* modelGround2_ = nullptr;
	//�X�e�[�W�̕�
	const static int stageSize = 11;//�^�񒆂�����Ƃ����̂Ŋ

	Object3d* objGround_[stageSize][stageSize] = {};

	XMINT2 selectFloor;
	bool IsGoal = false;//goalFloor�ɕۑ����邩�ۂ�
	int selectSoldier = 5;//�����I�����ĂȂ��Ƃ���5
	XMINT2 startFloor[4];
	XMINT2 goalFloor[4];
	  
	XMINT2 spawnFloor[4];
	XMFLOAT3 soldiersPos[4];//�e�����̈ʒu

	XMINT2 soldiersFloor[4];
};

