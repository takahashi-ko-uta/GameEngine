#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Model.h"

class Player
{
public://�����o�֐�
	//������
	void Initialize(Input* input);
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	//�ړ�
	void Move();
	//��]
	void Rotate();
	//�`��
	void Draw();

private://�����o�ϐ�
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;
};

