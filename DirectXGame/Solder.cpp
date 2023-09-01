#include "Solder.h"
#include "imgui.h"

#pragma region Normal
void Normal::Initialize(int soldierNum,int normalNum)
{
    this->normalNum_ = normalNum;
    //���f���ǂݍ���
    model_ = Model::LoadFromOBJ("Soldier");
    //���̃��f��������
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
    //�����̗͂�0�ȉ��Ȃ琶���t���O��false��
    if (life <= 0) {
        isLife = false;
    }

    //���[�_�[�̈ʒu�ۑ�
    leaderPos = pos;
    XMFLOAT3 objPos = obj_->GetPosition();

    switch (normalNum_)
    {
    case 0://��
        goalPos = { leaderPos.x,leaderPos.y,leaderPos.z + 3.0f };
        break;

    case 1://�E��
        goalPos = { leaderPos.x + 3.0f,leaderPos.y,leaderPos.z + 3.0f };
        break;

    case 2://�E
        goalPos = { leaderPos.x + 3.0f,leaderPos.y,leaderPos.z };
        break;

    case 3://�E��
        goalPos = { leaderPos.x + 3.0f,leaderPos.y,leaderPos.z - 3.0f };
        break;

    case 4://��
        goalPos = { leaderPos.x,leaderPos.y,leaderPos.z - 3.0f };
        break;

    case 5://����
        goalPos = { leaderPos.x - 3.0f,leaderPos.y,leaderPos.z - 3.0f };
        break;

    case 6://��
        goalPos = { leaderPos.x - 3.0f,leaderPos.y,leaderPos.z };
        break;

    case 7://����
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
    //���f���ǂݍ���
    model_ = Model::LoadFromOBJ("Soldier");
    //���̃��f��������
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
    //�����̗͂�0�ȉ��Ȃ琶���t���O��false��
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
    //�����̃��[�g�̏�����
    soldierRoute_ = new SoldierRoute();
    soldierRoute_->Initialize(spawnPos, soldierNum);

    //���[�_�[(�^�񒆂̂��)�̏�����
    leader = new Leader();
    leader->Initialize(soldierNum);
    //���̑��̕����̏�����
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
    //�����̈ʒu�Ɛ����t���O���܂Ƃ߂�
    //0�Ƀ��[�_�[
    soldiersPos_[0] = leader->GetPosition();
    isSoldiersLife_[0] = leader->GetIsLife();
    //1�`8�ɂ��̑�
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

