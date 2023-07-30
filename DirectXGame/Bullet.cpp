#include "Bullet.h"

void Bullet::Initialize(Vector3 pos, const Vector3& velocity)
{
	input_ = Input::GetInstance();
	this->pos_ = pos;
	velocity_ = velocity;

	//オブジェクトの生成
	model_ = Model::LoadFromOBJ("sphere");
	obj_ = Object3d::Create();
	obj_->SetModel(model_);
	obj_->SetScale({ 1.0f,1.0f,1.0f });
	obj_->SetPosition({ (float)pos_.x, (float)pos_.y, (float)pos_.z });

}

void Bullet::Finalize()
{
	delete model_;
	delete obj_;
}

void Bullet::Update()
{
	//時間経過で弾を消す
	if (--deathTimer <= 0) {
		isDead = true;
	}

	//XMFLOAT3 move = obj_->GetPosition();
	Vector3 move = { obj_->GetPosition().x,obj_->GetPosition().y ,obj_->GetPosition().z };

	move.x += velocity_.x;
	move.y += velocity_.y;
	move.z += velocity_.z;

	obj_->SetVecPosition(move);


	obj_->Update();
}

void Bullet::Draw()
{
	obj_->Draw();
}
