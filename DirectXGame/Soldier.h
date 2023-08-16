#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Input.h"
#include "SearchRoute.h"

class Soldier
{
public:
	//������
	void Initialize(XMFLOAT3 spawnPos, int soldierNum);
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMINT2 startFloor, XMINT2 goalFloor, XMFLOAT3 floorPos[11][11]);
	//�ړ�
	void Move();
	//���[�g�쐬
	void CreateRoute();
	//�����̈ʒu����(XMINT2�^)�ɕύX
	void ChangeSoldierFloor();
	//�X�|�[���̈ʒu����(XMINT2�^)�ɕύX
	void ChangeSpawnFloor();

	//�`��
	void Draw();

	//getter
	const XMFLOAT3 GetPosition() const { return obj_->GetPosition(); }

private:
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	XMFLOAT3 spawnPos_;	//�����ʒu
	XMINT2 spawnFloor_;
	XMINT2 startFloor;	//�X�^�[�g�ʒu
	XMINT2 goalFloor;	//�S�[���ʒu

	SearchRoute* searchRoute_ = nullptr;
	SearchRoute::Cell start_ = SearchRoute::Cell(0, 0);
	SearchRoute::Cell goal_ = SearchRoute::Cell(0, 0);
	XMINT2 route_[40];
	XMFLOAT3 floorPos[11][11];
	XMINT2 soldierFloor;

};

