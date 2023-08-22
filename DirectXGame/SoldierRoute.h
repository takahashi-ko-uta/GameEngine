#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Input.h"
#include "SearchRoute.h"
using namespace DirectX;

/// <summary>
/// �����̈ʒu
/// </summary>
class SoldierRoute
{
public:
	//������
	void Initialize(XMFLOAT3 spawnPos, int soldierNum);
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMINT2 startFloor, XMINT2 goalFloor, XMFLOAT3 floorPos[11][11], int selectSoldier, int costMap[11][11]);
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

	int soldierNum_;
	XMFLOAT3 spawnPos_;	//�����ʒu
	XMINT2 spawnFloor_;
	XMINT2 startFloor_;	//�X�^�[�g�ʒu
	XMINT2 goalFloor_;	//�S�[���ʒu

	SearchRoute* searchRoute_ = nullptr;
	SearchRoute::Cell start_ = SearchRoute::Cell(0, 0);
	SearchRoute::Cell goal_ = SearchRoute::Cell(0, 0);
	XMINT2 route_[40];
	int32_t routeNum_ = 0;
	bool isMove_ = false;//�ړ����Ă��邩
	XMFLOAT3 floorPos_[11][11];
	XMINT2 soldierFloor_;

	bool isSelect_ = false;//���ܑI�΂�Ă��邩
	int costMap_[11][11];
};

