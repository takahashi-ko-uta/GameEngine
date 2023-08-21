#include "Solder.h"

#pragma region Leader
void Leader::Initialize()
{
    //���f���ǂݍ���
    model_ = Model::LoadFromOBJ("Soldier");
    //���̃��f��������
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 1.0f,1.0f,1.0f });
}

void Leader::Finalize()
{

}

void Leader::Update(XMFLOAT3 pos)
{
    obj_->SetPosition(pos);
    obj_->Update();
}

void Leader::Draw()
{
    obj_->Draw();
}
#pragma endregion


#pragma region Solider
void Solider::Initialize()
{
    //���[�_�[�̏�����
    leader = new Leader();
    leader->Initialize();

}

void Solider::Finalize()
{

}

void Solider::Update(XMFLOAT3 pos)
{
    leader->Update(pos);
}

void Solider::Draw()
{
    leader->Draw();
}
#pragma endregion


