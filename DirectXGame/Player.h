#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Model.h"
#include <memory>
#include <list>

#include "Bullet.h"
#include "WorldTransform.h"

class Player
{
public://�����o�֐�
	//������
	void Initialize();
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
	
	Vector3 PLpos;
	std::list<std::unique_ptr<Bullet>> bullets_;
	WorldTransform w;
	Vector3 velocity;
};

