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
	//�X�e�[�W�̕�
	const static int stageSize = 11;//�^�񒆂�����Ƃ����̂Ŋ

	Object3d* objGround_[stageSize][stageSize] = {};

	XMFLOAT2 selectFloor;
	XMFLOAT2 startFloor = { 99.0f,99.0f };	//���肦�Ȃ����l�����Ƃ�
	XMFLOAT2 goalFloor = { 99.0f,99.0f };	//���肦�Ȃ����l�����Ƃ�
};

