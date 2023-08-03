#include "Player.h"
#include "imgui.h"
#include "affinTransformation.h"
#include "Vector3Math.h"

#define PI 3.14159265359

void Player::Initialize(Camera* camera)
{
	input_ = Input::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	camera_ = camera;
	//�X�v���C�g
	spriteCommon_ = SpriteCommon::GetInstance();
	//�e�N�X�`���̃Z�b�g
	reticle_ = new Sprite();
	reticle_->Initialize(spriteCommon_, 0, { 0.5f, 0.5f });
	reticle_->SetSize({ 50,50 });

	//�I�u�W�F�N�g�̐���
	model_ = Model::LoadFromOBJ("ProtrudingObject");
	obj_ = Object3d::Create();
	obj_->SetModel(model_);
	obj_->SetScale({ 3.0f,3.0f,3.0f });
	PLworldTransform.Initialize();

	model3Dreticle_ = Model::LoadFromOBJ("cube");
	obj3Dreticle_ = Object3d::Create();
	obj3Dreticle_->SetModel(model3Dreticle_);
	obj3Dreticle_->SetScale({ 3.0f,3.0f,3.0f });
	RTworldTransform.Initialize();
}

void Player::Finalize()
{
}

void Player::Update()
{
	//obj����worldTransform���擾
	PLworldTransform.matWorld = obj_->GetMat4World();
	RTworldTransform.matWorld = obj3Dreticle_->GetMat4World();

	//Move();
	//Rotate();
	//Attack();
	//Reticle3D();

	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) {
		return bullet->IsDead();
	});

	ImGui::Text("velocity(X:%f, Y:%f, Z:%f)", velocity.x, velocity.y, velocity.z);

	//�e���t���[������
	reticle_->Update();
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->Update();
	}
	PLworldTransform.Update();
	obj_->Update();
	RTworldTransform.Update();
	obj3Dreticle_->Update();
}

void Player::Move()
{
	//�ړ���
	float move = 0.3f;

	XMFLOAT3 pos = obj_->GetPosition();

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
		//�e�̑��x
		const float speed = 0.05f;
		velocity = { 0.0f,0.0f,speed };
		
		//���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		velocity = Vector3Math::diff(RTworldTransform.GetWorldPosition(), PLworldTransform.GetWorldPosition());
		velocity = Vector3Math::Normalize(velocity) * speed;
		//velocity = Matrix4::Vector3Mat(velocity, PLworldTransform.matWorld);

		//�e�̐����Ə�����
		std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
		newBullet->Initialize(PLworldTransform.GetWorldPosition(), velocity);
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::Reticle3D()
{
	//���@����3D���e�B�N���ւ̋���
	const float kDistancePlayerTo3DReticle = 50.0f;
	//���@����3D���e�B�N���ւ̃I�t�Z�b�g(z+����)
	Vector3 offset = { 0, 0, 1.0f };
	//���@�̃��[���h�s��̉�]�𔽉f
	offset = Matrix4::Vector3Mat(offset, PLworldTransform.matWorld);//
	//�x�N�g���̒����𐮂���
	offset = Vector3Math::Normalize(offset) * kDistancePlayerTo3DReticle;
	//3D���e�B�N���̍��W��ݒ�
	Vector3 retcle3DPos = { 0.0f,0.0f,kDistancePlayerTo3DReticle };
	retcle3DPos = Matrix4::Vector3Mat(retcle3DPos, PLworldTransform.matWorld);//
	retcle3DPos.x = retcle3DPos.x + PLworldTransform.GetWorldPosition().x;
	retcle3DPos.y = retcle3DPos.y + PLworldTransform.GetWorldPosition().y;
	retcle3DPos.z = retcle3DPos.z + PLworldTransform.GetWorldPosition().z;

	obj3Dreticle_->SetPosition({ retcle3DPos.x, retcle3DPos.y, retcle3DPos.z });

	//3D���e�B�N���̃��[���h���W���擾
	Vector3 retcle2DPos = RTworldTransform.GetWorldPosition();

	//�r���[�s��A�v���W�F�N�V�����s��A�r���[�|�[�g�s����擾
	Matrix4 matView = Vector3Math::ConvertMatrix4(camera_->GetMatView());
	Matrix4 matProjection = Vector3Math::ConvertMatrix4(camera_->GetMatProjection());
	Matrix4 matViewport = Matrix4::CreateViewport(WinApp::window_width, WinApp::window_height,offset);

	//�r���[�s��A�v���W�F�N�V�����s��A�r���[�|�[�g�s�������
	Matrix4 matVPV = matView * matProjection * matViewport;

	//���[���h���X�N���[�����W�ϊ�
	retcle2DPos = Matrix4::MatZdivision(retcle2DPos, matVPV);

	//�X�v���C�g�̃��e�B�N���ɍ��W�ݒ�
	reticle_->SetPosition({ retcle2DPos.x, retcle2DPos.y });

	ImGui::Text("PlayerPos(X:%f, Y:%f, Z:%f)", obj_->GetPosition().x, obj_->GetPosition().y, obj_->GetPosition().z);
	ImGui::Text("retcle3DPos(X:%f, Y:%f, Z:%f)", retcle3DPos.x, retcle3DPos.y, retcle3DPos.z);
	ImGui::Text("retcle2DPos(X:%f, Y:%f, Z:%f)", retcle2DPos.x, retcle2DPos.y, retcle2DPos.z);
	ImGui::Text("RT2DPos-RT3Dpos(X:%f, Y:%f)", retcle2DPos.x - WinApp::window_width/2, retcle2DPos.y - WinApp::window_height/2);
}

void Player::Reticle2D()
{
	//�E�B���h�E�̃}�E�X���W���擾
	XMFLOAT2 mousePos = input_->GetMouseWindowPos();

	//�r���[�s��A�v���W�F�N�V�����s��A�r���[�|�[�g�s��̍��v�s����v�Z����
	Matrix4 matVPV;
	//�����s��̋t�s����v�Z����
	Matrix4 matInverseVPV;
}

void Player::Draw()
{
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->Draw();
	}
	obj3Dreticle_->Draw();
	obj_->Draw();
}

void Player::DrawUI()
{
	reticle_->Draw();
}
