#pragma once
#include "Model.h"
#include "Object3d.h"

class GameStage
{
public://�����o�֐�
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	//�`��
	void Draw();
private://�����o�ϐ�
	Model* modelGround1_ = nullptr;
	Model* modelGround2_ = nullptr;
	Object3d* objGround_[5][5] = {};
};

