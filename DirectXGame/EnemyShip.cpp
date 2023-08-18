#include "EnemyShip.h"

void EnemyShip::Initialize()
{
    //ƒ‚ƒfƒ‹“Ç‚Ýž‚Ý
    model_ = Model::LoadFromOBJ("boat");
    //‹…‚Ìƒ‚ƒfƒ‹‰Šú‰»
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetPosition({ 60.0f,3.0f,0.0f });
    obj_->SetScale({ 1.5f,1.0f,1.5f });
}

void EnemyShip::Finalize()
{

}

void EnemyShip::Update()
{

    obj_->Update();
}

void EnemyShip::Draw()
{
    obj_->Draw();
}
