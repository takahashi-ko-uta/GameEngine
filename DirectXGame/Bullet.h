#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Model.h"

class Bullet
{
public://�����o�֐�
	//������
	void Initialize(Input* input, XMFLOAT3 pos);
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	//�`��
	void Draw();

private://�����o�ϐ�
	Input* input_ = nullptr;
	XMFLOAT3 pos_;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;
};

