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

#include "GameCamera.h"
#include "GameSprite.h"
#include "GameStage.h"
#include "Player.h"
#include "Soldier.h"
#include "SearchRoute.h"
#include "EnemyShip.h"

class GamePlayScene
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

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Camera* camera_ = nullptr;
	//�X�v���C�g���ʕ��̐���
	SpriteCommon* spriteCommon_ = nullptr;

	//���f������
	Model* modelSphere_ = nullptr;
	//3D�I�u�W�F�N�g����
	Object3d* objSphere_ = nullptr;
	//�����蔻��
	Sphere sphere;
	Plane plane;
	Ray ray;
	//audio����
	Audio* audio_ = nullptr;

	//�Q�[���p�J����
	GameCamera* gameCamera_ = nullptr;
	//�Q�[���Ɏg���X�v���C�g
	GameSprite* gameSprite_ = nullptr;
	//�X�e�[�W
	GameStage* gameStage_ = nullptr;
	//Player
	Player* player_ = nullptr;

	//����(4����)
	Soldier* soldier_[4];
	XMFLOAT3 soldiersPos_[4];//�e�����̈ʒu
	XMINT2 startFloor[4];
	XMINT2 goalFloor[4];
	XMFLOAT3 floorPos[11][11];

	//�G
	EnemyShip* ENship = nullptr;
};

