#pragma once
#include "Model.h"
#include "Object3d.h"




class Leader
{
public:
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMFLOAT3 pos);
	//�`��
	void Draw();

private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

};


class Solider
{
public:
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMFLOAT3 pos);
	//�`��
	void Draw();
private:
	Leader* leader = nullptr;
};