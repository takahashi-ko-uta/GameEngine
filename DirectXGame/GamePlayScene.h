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
	//3D�I�u�W�F�N�g����
	Object3d* objGround_ = nullptr;
	//�����蔻��
	Sphere sphere;
	Plane plane;
	Ray ray;
	//audio����
	Audio* audio_ = nullptr;
	XMFLOAT3 cameraEye = { 0,0,0 };
};

