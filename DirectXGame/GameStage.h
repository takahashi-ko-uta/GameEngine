#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Input.h"

class GameStage
{
public://�����o�֐�
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	void Select();
	//�`��
	void Draw();
private://�����o�ϐ�
	Input* input = nullptr;
	Model* modelGround1_ = nullptr;
	Model* modelGround2_ = nullptr;
	Object3d* objGround_[5][5] = {};

	int selectX = 0;
	int selectY = 0;
};

