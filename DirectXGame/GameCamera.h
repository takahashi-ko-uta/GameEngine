#pragma once
#include "Camera.h"
#include "DirectXCommon.h"
#include "Input.h"

struct RotateObject
{
	float m_PosX;		// �`����WX
	float m_PosY;		// �`����WY
	float m_Radius;		// ���a(�`��p)
	float m_CenterX;	// ���S���WX
	float m_CenterY;	// ���S���WY
	float m_Angle;		// �p�x
	float m_Length;		// ���a�̒���
};

class GameCamera
{
public://�����o�֐�
	//������
	void Initialize(Camera* camera);
	//�I��
	void Finalize();
	//���t���[������
	void Update();


private://�����o�ϐ�
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Camera* camera_ = nullptr;

	//��]�^��
	RotateObject rotObj =
	{
		0,		//�`����WX
		0,		//�`����WY
		10,		//���a(�`��p)
		0,		//���S���WX
		0,		//���S���WY
		0.0f,	//�p�x
		50.0f,	//���a�̒���
	};

	// �x���@�̊p�x���ʓx�@�ɕϊ�
	float radius = rotObj.m_Angle * 3.14f / 180.0f;

	// �O�p�֐����g�p���A�~�̈ʒu������o���B
	float add_x = cos(radius) * rotObj.m_Length;
	float add_y = sin(radius) * rotObj.m_Length;
};

