#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Model.h"

class Bullet
{
public://�����o�֐�
	//������
	void Initialize(Vector3 pos, const Vector3& velocity);
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	//�`��
	void Draw();

	//getter
	bool IsDead() const { return isDead; }

private://�����o�ϐ�
	Input* input_ = nullptr;
	Vector3 pos_;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	Vector3 velocity_;
	//������܂ł̎���
	static const int32_t lifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathTimer = lifeTime;
	//�f�X�t���O
	bool isDead = false;
};

