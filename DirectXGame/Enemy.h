#pragma once
#include "EnemyShip.h"
#include "SoldierRoute.h"

class EnemyNormal
{
public:
	//������
	void Initialize(int soldierNum);
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMFLOAT3 pos);
	//�`��
	void Draw();

	//getter
	XMFLOAT3 GetPosition() { return obj_->GetPosition(); }
	bool GetIsLife() { return isLife; }
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	int soldierNum_;
	XMFLOAT3 leaderPos;//�w�肳��Ă��鏰�̍��W
	XMFLOAT3 goalPos;//�ړI�n

	bool isLife = true; //�����t���O
	int32_t life = 3;	//�̗�
};

class EnemyLeader
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
	bool GetIsLife() { return isLife; }
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;
	SearchRoute* enemyRoute_ = nullptr;
	XMFLOAT3 floorPos_[11][11];//���̍��W
	XMFLOAT3 shipPos_;
	bool isChangeMap = true;
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

	bool isLife = true; //�����t���O
	int32_t life = 3;	//�̗�
};

//�G�̂ЂƂ����܂�
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

	//setter
	void SetIsStart(bool isStart) { this->isStart_ = isStart; }

	//getter
	//�G�S���̈ʒu�Ɛ����t���O���擾�ł���
	void GetEnemysStatus(XMFLOAT3 enemysPos[9], bool isEnemysLife[9]);
private:
	EnemyShip* ship_ = nullptr;
	EnemyLeader* leader_ = nullptr;
	EnemyNormal* normal_[8];//�ő�8�l����
	int32_t enemyNum;//�G(normal)�̐�
	bool isStart_;

	XMFLOAT3 enemysPos_[9];//�G�S���̈ʒu
	bool isEnemysLife_[9]; //�G�S���̐����t���O
};

class Enemy
{
public:
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMFLOAT3 floorPos[11][11], XMINT2 houseFloor[3], int costMap[11][11]);
	//�X�|�[��
	void Spawn();
	//�`��
	void Draw();

	//getter
	//�G�S���̈ʒu�Ɛ����t���O���擾�ł���
	void GetEnemysStatus(XMFLOAT3 enemysPos[45], bool isEnemysLife[45]);

	//setter
	void SetSoldiersStatus(XMFLOAT3 soldiersPos[36], bool isSoldiersLife[36]);

private:
	EnemySoldier* soldier[5];
	bool isStartShip[5];
	int32_t spawnTime;
	int32_t num;
	bool isSpawn = true;
	bool isDelete = false;
	int32_t enemyNum;//�G(normal)�̐�

	XMFLOAT3 enemysPos_[45];//�G�S���̈ʒu
	bool isEnemysLife_[45]; //�G�S���̐����t���O

	XMFLOAT3 soldiersPos_[36];//�����S���̈ʒu
	bool isSoldiersLife_[36]; //�����S���̐����t���O
};

