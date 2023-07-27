#include "Bullet.h"

void Bullet::Initialize(Input* input, XMFLOAT3 pos)
{
	this->input_ = input;
	this->pos_ = pos;

	//オブジェクトの生成
	model_ = Model::LoadFromOBJ("sphere");
	obj_ = Object3d::Create();
	obj_->SetModel(model_);
	obj_->SetScale({ 1.0f,1.0f,1.0f });
	obj_->SetPosition(pos);

}

void Bullet::Finalize()
{
	delete model_;
	delete obj_;
}

void Bullet::Update(XMFLOAT3 velocity)
{
	velocity_ = velocity;
	XMFLOAT3 move = obj_->GetPosition();

	move.x += velocity_.x;
	move.y += velocity_.y;
	move.z += velocity_.z;

	obj_->SetPosition(move);

	obj_->Update();
}

void Bullet::Draw()
{
	obj_->Draw();
}
