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
	void Update(XMFLOAT3 pos, XMINT2 goal, bool isGoal, XMFLOAT3 floorPos[11][11], XMINT2 houseFloor[3], XMFLOAT3 routePos);
	//��ԋ߂��Ƃ�������
	void SearchHouse(XMINT2 houseFloor[3]);
	//�D�ɏ���Ă�Ƃ�
	void OnShip(bool isGoal);
	//��������
	void Landing(XMINT2 goal);
	//�Ƃ̋߂��܂œ���
	void Move();
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

	XMFLOAT3 floorPos_[11][11];//���̍��W
	XMFLOAT3 shipPos_;
	XMFLOAT3 routePos_;
	bool isOnShip = true;
	bool isLanding = false;
	bool isMove = false;
	XMINT2 nowFloor;	//�����鏰
	XMINT2 goalFloor;
	XMFLOAT3 housePos[3];
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
