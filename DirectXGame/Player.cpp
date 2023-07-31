#include "Player.h"
#include "imgui.h"
#include "affinTransformation.h"

#define PI 3.14159265359

void Player::Initialize()
{
	input_ = Input::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();

	//�I�u�W�F�N�g�̐���
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
	Attack();
	
	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) {
		return bullet->IsDead();
	});

	
	ImGui::Text("velocity(X:%f, Y:%f, Z:%f)", velocity.x, velocity.y, velocity.z);

	ImGui::Text("objPos(X:%f, Y:%f, Z:%f)", obj_->GetPosition().x, obj_->GetPosition().y, obj_->GetPosition().z);
	ImGui::Text("wldPos(X:%f, Y:%f, Z:%f)", w.translation.x, w.translation.y, w.translation.z);

	ImGui::Text("objRot(X:%f, Y:%f, Z:%f)", obj_->GetRotation().x, obj_->GetRotation().y, obj_->GetRotation().z);
	ImGui::Text("wldRot(X:%f, Y:%f, Z:%f)", w.rotation.x, w.rotation.y, w.rotation.z);

	//�e���t���[������
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->Update();
	}
	w.Update();
	obj_->Update();
}

void Player::Move()
{
	//�ړ���
	float move = 0.3f;

	
	XMFLOAT3 pos = obj_->GetPosition();

	//pos.z = -50.0f;

	//�ړ�
	if (input_->PushKey(DIK_W)) { pos.y += move; }
	if (input_->PushKey(DIK_S)) { pos.y -= move; }
	if (input_->PushKey(DIK_A)) { pos.x -= move; }
	if (input_->PushKey(DIK_D)) { pos.x += move; }

	//���f
	obj_->SetPosition(pos);
}

void Player::Rotate()
{
	XMFLOAT3 rot = obj_->GetRotation();

	//��]
	if (input_->PushKey(DIK_UP)) { rot.x -= 10 * PI / 180; }
	if (input_->PushKey(DIK_DOWN)) { rot.x += 10 * PI / 180; }
	if (input_->PushKey(DIK_LEFT)) { rot.y -= 10 * PI / 180; }
	if (input_->PushKey(DIK_RIGHT)) { rot.y += 10 * PI / 180; }

	//���f
	obj_->SetRotation(rot);
}

void Player::Attack()
{
	if (input_->TriggerMouseLeft()) {
		//obj����worldTransform���擾
		w.matWorld = obj_->GetMat4World();

		//�e�̑��x
		const float speed = 3.0f;
		velocity = { 0.0f,0.0f,speed };
		
		//���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		velocity = Matrix4::Transform(velocity, w.matWorld);

		//�e�̐����Ə�����
		std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
		newBullet->Initialize(w.GetWorldPosition(), velocity);
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
