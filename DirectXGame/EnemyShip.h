#pragma once
#include "Input.h"
#include "Model.h"
#include "Object3d.h"

class EnemyShip
{
public:
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMFLOAT3 floorPos[11][11]);
	//�D�̃S�[�������߂�
	void CreateGoal(XMFLOAT3 floorPos[11][11]);
	//�D���o�����Ă��璅������܂ł̓���
	void Move();
	//�`��
	void Draw();

	//getter
	XMFLOAT3 GetPosition() { return obj_->GetPosition(); }
	XMINT2 GetGoalFloor() { return goalFloor; }
	bool GetIsGoal() { return isGoal; }

	//setter
	void SetIsStart(bool isStart) { this->isStart = isStart; }
private:
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	int32_t direction = 0;
	int32_t floorNum = 0;
	int num;
	bool isStart = false;
	bool isSpawn = true;  //�X�|�[���ɕK�v�Ȓl�����߂�
	bool isSelect = false;//�S�[���ʒu�����߂�
	bool isMove = false;  //�����܂œ���
	bool isGoal = false;  //�S�[��������
	XMINT2 goalFloor;
	XMFLOAT3 startPos;
	XMFLOAT3 goalPos;
	XMFLOAT3 floorPos_[11][11];
	float randomPos;//�X�^�[�g�ʒu�������_���ɂ���
};

