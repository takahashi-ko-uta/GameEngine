#include "Player.h"
#include "imgui.h"
#include "affinTransformation.h"

#define PI 3.14159265359

void Player::Initialize()
{
	input_ = Input::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();

	//オブジェクトの生成
	model_ = Model::LoadFromOBJ("ProtrudingObject");
	obj_ = Object3d::Create();
	obj_->SetModel(model_);
	obj_->SetScale({ 3.0f,3.0f,3.0f });
	w.Initialize();
}

void Player::Finalize()
{
}

void Player::Update()
{
	XMFLOAT3 pos = obj_->GetPosition();
	XMFLOAT3 scale = obj_->GetScale();
	XMFLOAT3 rot = obj_->GetRotation();


	Move();
	Rotate();
	
	//w = obj_->GetWorldTransform();
	w.translation = { pos.x, pos.y, pos.z };
	w.scale = { scale.x,scale.y,scale.z };
	w.rotation = { rot.x,rot.y,rot.z };
	w.Update();

	PLpos = w.translation;
	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) {
		return bullet->IsDead();
	});

	Attack();

	ImGui::Text("velocity(X:%f, Y:%f, Z:%f)", velocity.x, velocity.y, velocity.z);

	ImGui::Text("objPos(X:%f, Y:%f, Z:%f)", obj_->GetPosition().x, obj_->GetPosition().y, obj_->GetPosition().z);
	ImGui::Text("wldPos(X:%f, Y:%f, Z:%f)", w.translation.x, w.translation.y, w.translation.z);

	ImGui::Text("objRot(X:%f, Y:%f, Z:%f)", obj_->GetRotation().x, obj_->GetRotation().y, obj_->GetRotation().z);
	ImGui::Text("wldRot(X:%f, Y:%f, Z:%f)", w.rotation.x, w.rotation.y, w.rotation.z);

	w.Update();
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->Update();
	}
	obj_->Update();
}

void Player::Move()
{
	//移動量
	float move = 0.3f;

	
	XMFLOAT3 pos = obj_->GetPosition();

	//pos.z = -50.0f;

	//移動
	if (input_->PushKey(DIK_W)) { pos.y += move; }
	if (input_->PushKey(DIK_S)) { pos.y -= move; }
	if (input_->PushKey(DIK_A)) { pos.x -= move; }
	if (input_->PushKey(DIK_D)) { pos.x += move; }

	//反映
	obj_->SetPosition(pos);
}

void Player::Rotate()
{
	XMFLOAT3 rot = obj_->GetRotation();

	//回転
	if (input_->PushKey(DIK_UP)) { rot.x -= 10 * PI / 180; }
	if (input_->PushKey(DIK_DOWN)) { rot.x += 10 * PI / 180; }
	if (input_->PushKey(DIK_LEFT)) { rot.y -= 10 * PI / 180; }
	if (input_->PushKey(DIK_RIGHT)) { rot.y += 10 * PI / 180; }

	//反映
	obj_->SetRotation(rot);
}

void Player::Attack()
{
	if (input_->TriggerMouseLeft()) {
		//弾の速度
		const float speed = 3.0f;
		velocity = { 0.0f,0.0f,speed };

		velocity.x = (velocity.x * w.matWorld.m[0][0]) +
			(velocity.y * w.matWorld.m[1][0]) +
			(velocity.z * w.matWorld.m[2][0]) +
			(0 * w.matWorld.m[3][0]);

		velocity.y = (velocity.x * w.matWorld.m[0][1]) +
			(velocity.y * w.matWorld.m[1][1]) +
			(velocity.z * w.matWorld.m[2][1]) +
			(0 * w.matWorld.m[3][1]);

		velocity.z = (velocity.x * w.matWorld.m[0][2]) +
			(velocity.y * w.matWorld.m[1][2]) +
			(velocity.z * w.matWorld.m[2][2]) +
			(0 * w.matWorld.m[3][2]);


		std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
		newBullet->Initialize(PLpos, velocity);

		bullets_.push_back(std::move(newBullet));
	}
}

void Player::Draw()
{
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->Draw();
	}

	obj_->Draw();
}
