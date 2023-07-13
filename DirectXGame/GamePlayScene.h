#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Audio.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionPrimitive.h"
#include "ParticleManager.h"

struct DrawObject
{
	float m_PosX;		// �`����WX
	float m_PosY;		// �`����WY
	float m_Radius;		// ���a(�`��p)
	float m_CenterX;	// ���S���WX
	float m_CenterY;	// ���S���WY
	float m_Angle;		// �p�x
	float m_Length;		// ���a�̒���
};

class GamePlayScene
{
public://�����o�֐�
	//������
	void Initialize(DirectXCommon* dxCommon, Input* input);
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	//�`��
	void Draw();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Camera* camera_ = nullptr;
	//�X�v���C�g���ʕ��̐���
	SpriteCommon* spriteCommon_ = nullptr;
	//�X�v���C�g����
	Sprite* sprite1_ = nullptr;
	Sprite* sprite2_ = nullptr;
	//�p�[�e�B�N������
	ParticleManager* particle1_ = nullptr;
	ParticleManager* particle2_ = nullptr;
	//���f������
	Model* modelGround1_ = nullptr;
	Model* modelGround2_ = nullptr;
	Model* modelSphere_ = nullptr;
	//3D�I�u�W�F�N�g����
	Object3d* objGround_[5][5] = {};
	Object3d* objSphere_ = nullptr;
	//�����蔻��
	Sphere sphere;
	Plane plane;
	Ray ray;
	//audio����
	Audio* audio_ = nullptr;
	XMFLOAT3 cameraEye = { 0,0,0 };

	//��]�^��
	DrawObject rotObj =
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

