#include "EnemyShip.h"

void EnemyShip::Initialize()
{
    //モデル読み込み
    model_ = Model::LoadFromOBJ("cube");
    //球のモデル初期化
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 1.0f,1.0f,1.0f });
    //obj_->SetPosition({ spawnPos_.x,6.0f,spawnPos_.z });
}

void EnemyShip::Finalize()
{

}

void EnemyShip::Update()
{

}

void EnemyShip::Draw()
{

}
