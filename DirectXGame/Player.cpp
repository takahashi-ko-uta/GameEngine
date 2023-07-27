#include "Player.h"
#define PI 3.14159265359

void Player::Initialize(Input* input, DirectXCommon* dxCommon)
{
	this->input_ = input;
	this->dxCommon_ = dxCommon;
	//ƒIƒuƒWƒFƒNƒg‚Ì¶¬
	model_ = Model::LoadFromOBJ("ProtrudingObject");
	obj_ = Object3d::Create();
	obj_->SetModel(model_);
	obj_->SetScale({ 3.0f,3.0f,3.0f });

	worldTransform.Initialize(dxCommon_);
}

void Player::Finalize()
{
}

void Player::Update()
{
	Move();
	Rotate();
	Attack();

	//’e‚ÌXV
	if (bullet_) {
		XMFLOAT3 velocity = { 0.0f,0.0f,3.0f };
		bullet_->Update(velocity);
	}

	obj_->Update();
}

void Player::Move()
{
	//ˆÚ“®—Ê
	float move = 0.3f;

	
	XMFLOAT3 pos = obj_->GetPosition();

	pos.z = -50.0f;

	//ˆÚ“®
	if (input_->PushKey(DIK_W)) { pos.y += move; }
	if (input_->PushKey(DIK_S)) { pos.y -= move; }
	if (input_->PushKey(DIK_A)) { pos.x -= move; }
	if (input_->PushKey(DIK_D)) { pos.x += move; }

	//”½‰f
	obj_->SetPosition(pos);
}

void Player::Rotate()
{
	XMFLOAT3 rot = obj_->GetRotation();

	//‰ñ“]
	if (input_->PushKey(DIK_UP)) { rot.x -= 10 * PI / 180; }
	if (input_->PushKey(DIK_DOWN)) { rot.x += 10 * PI / 180; }
	if (input_->PushKey(DIK_LEFT)) { rot.y -= 10 * PI / 180; }
	if (input_->PushKey(DIK_RIGHT)) { rot.y += 10 * PI / 180; }

	//”½‰f
	obj_->SetRotation(rot);
}

void Player::Attack()
{
	if (input_->TriggerMouseLeft()) {
		Bullet* newBullet = new Bullet();
		newBullet->Initialize(input_, obj_->GetPosition());

		bullet_ = newBullet;
	}
}

void Player::Draw()
{
	if (bullet_) {
		bullet_->Draw();
	}

	obj_->Draw();
}
