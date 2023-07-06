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
	Sprite* sprite_ = nullptr;
	//���f������
	Model* model_ = nullptr;
	Model* modelCube_ = nullptr;
	Model* modelSphere = nullptr;
	Model* modelPlane_ = nullptr;
	//3D�I�u�W�F�N�g����
	Object3d* objCube_ = nullptr;
	Object3d* objSphere_ = nullptr;
	Object3d* objPlane_ = nullptr;
	//�����蔻��
	Sphere sphere;
	Plane plane;
	Ray ray;
	//audio����
	Audio* audio_ = nullptr;
	XMFLOAT3 cameraEye = { 0,0,0 };
};

