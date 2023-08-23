#pragma once
#include "EnemyShip.h"
#include "SoldierRoute.h"

class Enemy
{
public:
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMFLOAT3 pos, XMINT2 goal, bool isGoal, XMFLOAT3 floorPos[11][11], int costMap[11][11], XMINT2 houseFloor[3]);
	void CreateRoute();
	//��ԋ߂��Ƃ�������
	void SearchHouse(XMINT2 houseFloor[3]);
	//�D�ɏ���Ă�Ƃ�
	void OnShip(bool isGoal);
	//��������
	void Landing(XMINT2 goal, XMINT2 houseFloor[3]);
	//�Ƃ̋߂��܂œ���
	void Move(XMINT2 houseFloor[3]);
	//�`��
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
	XMFLOAT3 floorPos_[11][11];//���̍��W
	XMFLOAT3 shipPos_;
	bool isOnShip = true;
	bool isLanding = false;
	bool isMove = false;
	XMINT2 nowFloor;	//�����鏰
	XMINT2 goalFloor;
	XMFLOAT3 housePos[3];
	SearchRoute::Cell start_ = SearchRoute::Cell(0, 0);
	SearchRoute::Cell goal_ = SearchRoute::Cell(0, 0);
	int costMap_[11][11];
	XMINT2 route[40];
	int32_t routeNum_ = 0;
};

class EnemySoldier
{
public:
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMFLOAT3 floorPos[11][11], XMINT2 houseFloor[3], int costMap[11][11]);
	//�`��
	void Draw();
private:
	EnemyShip* ship_ = nullptr;
	Enemy* enemy_ = nullptr;
	SoldierRoute* soldierRoute_ = nullptr;
};
