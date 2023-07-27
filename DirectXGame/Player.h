#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Model.h"

#include "Bullet.h"
#include "WorldTransform.h"

class Player
{
public://�����o�֐�
	//������
	void Initialize(Input* input, DirectXCommon* dxCommon);
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	//�ړ�
	void Move();
	//��]
	void Rotate();
	//�N���b�N
	void Attack();
	//�`��
	void Draw();

private://�����o�ϐ�
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Object3d* obj_ = nullptr;
	Bullet* bullet_ = nullptr;
	WorldTransform worldTransform;
};

