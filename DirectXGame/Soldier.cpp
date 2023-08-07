#include "Soldier.h"

void Soldier::Initialize(XMFLOAT3 spawnPos, int soldierNum)
{
	input_ = Input::GetInstance();
    this->spawnPos_ = spawnPos;
    //���f���ǂݍ���
    model_ = Model::LoadFromOBJ("Soldier");
    //���̃��f��������
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 1.0f,1.0f,1.0f });
    obj_->SetPosition({ spawnPos_.x,6.0f,spawnPos_.z });

    //soldierNum�ɂ���ĐF�ς���(0�`3�܂�)
    if (soldierNum == 0) { obj_->SetColor({ 1,0,0,1 }); }
    if (soldierNum == 1) { obj_->SetColor({ 0,1,0,1 }); }
    if (soldierNum == 2) { obj_->SetColor({ 0,0,1,1 }); }
    if (soldierNum == 3) { obj_->SetColor({ 1,0,1,1 }); }
}

void Soldier::Finalize()
{
    
}

void Soldier::Update()
{
    obj_->Update();
}

void Soldier::Draw()
{
    obj_->Draw();
}
