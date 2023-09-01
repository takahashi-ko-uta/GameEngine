#include "Solder.h"
#include "imgui.h"

#pragma region Normal
void Normal::Initialize(int soldierNum,int normalNum)
{
    this->normalNum_ = normalNum;
    //モデル読み込み
    model_ = Model::LoadFromOBJ("Soldier");
    //球のモデル初期化
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 0.5f,0.5f,0.5f });
    if (soldierNum == 0) { obj_->SetColor({ 1,0,0,1 }); }
    if (soldierNum == 1) { obj_->SetColor({ 0,1,0,1 }); }
    if (soldierNum == 2) { obj_->SetColor({ 0,0,1,1 }); }
    if (soldierNum == 3) { obj_->SetColor({ 1,0,1,1 }); }
}
void Normal::Finalize()
{

}
void Normal::Update(XMFLOAT3 pos)
{
    //もし体力が0以下なら生存フラグをfalseへ
    if (life <= 0) {
        isLife = false;
    }

    //リーダーの位置保存
    leaderPos = pos;
    XMFLOAT3 objPos = obj_->GetPosition();

    switch (normalNum_)
    {
    case 0://上
        goalPos = { leaderPos.x,leaderPos.y,leaderPos.z + 3.0f };
        break;

    case 1://右上
        goalPos = { leaderPos.x + 3.0f,leaderPos.y,leaderPos.z + 3.0f };
        break;

    case 2://右
        goalPos = { leaderPos.x + 3.0f,leaderPos.y,leaderPos.z };
        break;

    case 3://右下
        goalPos = { leaderPos.x + 3.0f,leaderPos.y,leaderPos.z - 3.0f };
        break;

    case 4://下
        goalPos = { leaderPos.x,leaderPos.y,leaderPos.z - 3.0f };
        break;

    case 5://左下
        goalPos = { leaderPos.x - 3.0f,leaderPos.y,leaderPos.z - 3.0f };
        break;

    case 6://左
        goalPos = { leaderPos.x - 3.0f,leaderPos.y,leaderPos.z };
        break;

    case 7://左上
        goalPos = { leaderPos.x - 3.0f,leaderPos.y,leaderPos.z + 3.0f };
        break;

    }

    obj_->SetPosition(goalPos);
    obj_->Update();
}
void Normal::Draw()
{
    obj_->Draw();
}
#pragma endregion

#pragma region Leader
void Leader::Initialize(int soldierNum)
{
    //モデル読み込み
    model_ = Model::LoadFromOBJ("Soldier");
    //球のモデル初期化
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 0.5f,0.5f,0.5f });
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
    //もし体力が0以下なら生存フラグをfalseへ
    if (life <= 0) {
        isLife = false;
    }

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

    //リーダー(真ん中のやつ)の初期化
    leader = new Leader();
    leader->Initialize(soldierNum);
    //その他の兵隊の初期化
    for (int i = 0; i < 8; i++) {
        normal[i] = new Normal();
        normal[i]->Initialize(soldierNum,i);
    }
    
}

void Solider::Finalize()
{

}

void Solider::Update(XMINT2 startFloor, XMINT2 goalFloor, XMFLOAT3 floorPos[11][11],int selectSoldier, int costMap[11][11])
{
    //兵隊の位置と生存フラグをまとめる
    //0にリーダー
    soldiersPos_[0] = leader->GetPosition();
    isSoldiersLife_[0] = leader->GetIsLife();
    //1～8にその他
    for (int i = 0; i < 8; i++) {
        soldiersPos_[i+1] = normal[i]->GetPosition();
        isSoldiersLife_[i+1] = normal[i]->GetIsLife();
    }

    soldierRoute_->Update(startFloor, goalFloor, floorPos,selectSoldier,costMap);
    leader->Update(soldierRoute_->GetPosition());
    for (int i = 0; i < 8; i++) {
        normal[i]->Update(leader->GetPosition());
    }
}

void Solider::Draw()
{
    soldierRoute_->Draw();
    leader->Draw();
    for (int i = 0; i < 8; i++) {
        normal[i]->Draw();
    }
}

void Solider::GetSoldiersStatus(XMFLOAT3 soldiersPos[9], bool isSoldiersLife[9])
{
    for (int i = 0; i < 9; i++) {
        soldiersPos[i] = this->soldiersPos_[i];
        isSoldiersLife[i] = this->isSoldiersLife_[i];
    }
}
#pragma endregion

