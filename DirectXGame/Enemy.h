#pragma once
#include "EnemyShip.h"

class Enemy
{
public:
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMFLOAT3 pos, XMINT2 goal, bool isGoal, XMFLOAT3 floorPos[11][11]);
	//�D�ɏ���Ă�Ƃ�
	void OnShip(bool isGoal);
	//��������
	void Landing(XMINT2 goal);
	//�`��
	void Draw();

	//getter
	XMFLOAT3 GetPosition() { return obj_->GetPosition(); }
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	XMFLOAT3 floorPos_[11][11];//���̍��W
	XMFLOAT3 shipPos_;
	bool isLanding = false;
};

class EnemySoldier
{
public:
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMFLOAT3 floorPos[11][11]);
	//�`��
	void Draw();
private:
	EnemyShip* ship_ = nullptr;
	Enemy* enemy_ = nullptr;
};
