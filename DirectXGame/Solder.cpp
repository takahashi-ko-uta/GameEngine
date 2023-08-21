#include "Solder.h"

#pragma region Leader
void Leader::Initialize(int soldierNum)
{
    //モデル読み込み
    model_ = Model::LoadFromOBJ("Soldier");
    //球のモデル初期化
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 1.0f,1.0f,1.0f });
    if (soldierNum == 0) { obj_->SetColor({ 1,0,0,1 }); }
    if (soldierNum == 1) { obj_->SetColor({ 0,1,0,1 }); }
    if (soldierNum == 2) { obj_->SetColor({ 0,0,1,1 }); }
    if (soldierNum == 3) { obj_->SetColor({ 1,0,1,1 }); }
}

void Leader::Finalize()
{

}

void Leader::Update(XMFLOAT3 pos)
{
    floorPos = {pos.x,0.0f,pos.z};
    XMFLOAT3 objPos = obj_->GetPosition();

    objPos = { floorPos.x,6.0f,floorPos.z };

    obj_->SetPosition(objPos);
    obj_->Update();
}

void Leader::Draw()
{
    obj_->Draw();
}
#pragma endregion


#pragma region Solider
void Solider::Initialize(XMFLOAT3 spawnPos, int soldierNum)
{
    //兵隊のルートの初期化
    soldierRoute_ = new SoldierRoute();
    soldierRoute_->Initialize(spawnPos, soldierNum);

    //リーダーの初期化
    leader = new Leader();
    leader->Initialize(soldierNum);

}

void Solider::Finalize()
{

}

void Solider::Update(XMINT2 startFloor, XMINT2 goalFloor, XMFLOAT3 floorPos[11][11],int selectSoldier)
{
    soldierRoute_->Update(startFloor, goalFloor, floorPos,selectSoldier);
    leader->Update(soldierRoute_->GetPosition());
}

void Solider::Draw()
{
    soldierRoute_->Draw();
    leader->Draw();
}
#pragma endregion


