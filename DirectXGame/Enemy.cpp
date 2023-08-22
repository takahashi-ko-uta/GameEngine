#include "Enemy.h"

#pragma region Enemy
void Enemy::Initialize()
{
    //���f���ǂݍ���
    model_ = Model::LoadFromOBJ("Soldier");
    //���̃��f��������
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 0.5f,0.5f,0.5f });
    obj_->SetColor({ 0,0,0,1 });
}

void Enemy::Finalize()
{

}

void Enemy::Update(XMFLOAT3 pos, XMINT2 goal, bool isGoal, XMFLOAT3 floorPos[11][11])
{
    shipPos_ = pos;//�D�̍��W��ۑ�
    
    for (int y = 0; y < 11; y++) {//���̍��W�ۑ�
        for (int x = 0; x < 11; x++) {
            this->floorPos_[y][x] = floorPos[y][x];
        }
    }

    //�D�̏�ɂ���Ƃ�
    OnShip(isGoal);


    Landing(goal);

    obj_->Update();
}

void Enemy::OnShip(bool isGoal)
{
    if (isGoal == false) {
        XMFLOAT3 objPos = obj_->GetPosition();

        objPos = { shipPos_.x,3.0f,shipPos_.z };

        obj_->SetPosition(objPos);
    }
    else{
        isLanding = true;
    }
}

void Enemy::Landing(XMINT2 goal)
{
    XMFLOAT3 goalPos = floorPos_[goal.x][goal.y];
    goalPos = { goalPos.x,6.0f,goalPos.z };//y������������
    XMFLOAT3 move = { 0.0f, 0.0f, 0.0f };
    XMFLOAT3 pos = obj_->GetPosition();
    float speed = 0.5f;

    //�ŏ��͊C�ɒ���ł��邽�߁A���W���グ��
    if (obj_->GetPosition().y <= goalPos.y) {
        move.y = speed;
    }
    else {
        move.y = 0.0f;
    }

    // �ړ���
    if (goalPos.x < obj_->GetPosition().x) {
        move.x = -speed;
    }
    else if (goalPos.x > obj_->GetPosition().x) {
        move.x = speed;
    }
    else {
        move.x = 0.0f;
    }

    if (goalPos.z < obj_->GetPosition().z) {
        move.z = -speed;
    }
    else if (goalPos.z > obj_->GetPosition().z) {
        move.z = speed;
    }
    else {
        move.z = 0.0f;
    }

    if (isLanding == true) {
        //�ړI�n�ɍs���܂ő�����
        if (goalPos.x != obj_->GetPosition().x ||
            goalPos.z != obj_->GetPosition().z) {

            //�ړ�
            pos.x += move.x;
            pos.y += move.y;
            pos.z += move.z;
            obj_->SetPosition(pos);
        }
        //�ړI�n�ɒ�������
        else if (goalPos.x == obj_->GetPosition().x &&
            goalPos.z == obj_->GetPosition().z) {
            //�t���O������
            isLanding = false;
        };
    }

}

void Enemy::Draw()
{
    obj_->Draw();
}
#pragma endregion


#pragma region EnemySoldier
void EnemySoldier::Initialize()
{
	ship_ = new EnemyShip();
	ship_->Initialize();

    enemy_ = new Enemy();
    enemy_->Initialize();

}

void EnemySoldier::Finalize()
{

}

void EnemySoldier::Update(XMFLOAT3 floorPos[11][11])
{
	ship_->Update(floorPos);
    enemy_->Update(ship_->GetPosition(),ship_->GetGoalFloor(),ship_->GetIsGoal(),floorPos);
}

void EnemySoldier::Draw()
{
	ship_->Draw();
    enemy_->Draw();
}

#pragma endregion