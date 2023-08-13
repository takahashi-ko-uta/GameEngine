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
	void Update();
	//�`��
	void Draw();

	//getter
	const XMFLOAT3 GetPosition() const { return obj_->GetPosition(); }

private:
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	XMFLOAT3 spawnPos_;//�����ʒu
};

