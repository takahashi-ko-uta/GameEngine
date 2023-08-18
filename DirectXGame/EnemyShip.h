#pragma once
#include "Model.h"
#include "Object3d.h"

class EnemyShip
{
public:
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	//�`��
	void Draw();
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;
};

