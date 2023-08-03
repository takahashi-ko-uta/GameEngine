#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Model.h"
#include <memory>
#include <list>
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Bullet.h"
#include "WorldTransform.h"

class Player
{
public://�����o�֐�
	//������
	void Initialize(Camera* camera);
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	//�ړ�
	void Move();
	//��]
	void Rotate();
	//�N���b�N
	void Attack();
	//3D�Ə�
	void Reticle3D();
	//2D�Ə�
	void Reticle2D();
	//�`��
	void Draw();
	void DrawUI();
private://�����o�ϐ�
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* spriteCommon_ = nullptr;
	Camera* camera_ = nullptr;

	Sprite* reticle_ = nullptr;

	Object3d* obj_ = nullptr;
	Model* model_ = nullptr;
	WorldTransform PLworldTransform;

	Object3d* obj3Dreticle_ = nullptr;
	Model* model3Dreticle_ = nullptr;
	WorldTransform RTworldTransform;

	Vector3 PLpos;
	std::list<std::unique_ptr<Bullet>> bullets_;
	Vector3 velocity;

	//Vector3 RetclePos;
};

