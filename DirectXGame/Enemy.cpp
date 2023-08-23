#include "Enemy.h"
#include "imgui.h"

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

void Enemy::Update(XMFLOAT3 pos, XMINT2 goal, bool isGoal, XMFLOAT3 floorPos[11][11], XMINT2 houseFloor[3], XMFLOAT3 routePos)
{
    shipPos_ = pos;//�D�̍��W��ۑ�
    routePos_ = routePos;

    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            this->floorPos_[y][x] = floorPos[y][x];//���̍��W�ۑ�

            //���̍��W��x,z�Ɗe����x,z���ׂČ덷+-5��������ۑ�����
            if ((floorPos_[y][x].x + 5) >= obj_->GetPosition().x && (floorPos_[y][x].x - 5) <= obj_->GetPosition().x &&
                (floorPos_[y][x].z + 5) >= obj_->GetPosition().z && (floorPos_[y][x].z - 5) <= obj_->GetPosition().z) {

                nowFloor = { y,x };//�����鏰
            }
        }
    }

    //��ԋ߂��Ƃ����
    SearchHouse(houseFloor);

    //�D�̏�ɂ���Ƃ�
    OnShip(isGoal);

    //�D���痤�֏オ��
    Landing(goal);

    //�߂��̉ƂɌ�����
    Move();

    obj_->Update();

    
    ImGui::Text("isOnShip:%d,isLanding:%d, isMove:%d", isOnShip, isLanding, isMove);
    ImGui::Text("enemyPos(%.0f, %.0f, %.0f)", obj_->GetPosition().x, obj_->GetPosition().y, obj_->GetPosition().z);
    ImGui::Text("routePos(%.0f, %.0f, %.0f)", routePos_.x, routePos_.y, routePos_.z);
    ImGui::Text("S(%d, %d), G(%d, %d)", nowFloor.x, nowFloor.y, goalFloor.x, goalFloor.y);
}

void Enemy::SearchHouse(XMINT2 houseFloor[3])
{
    //�S�[�����쐬
    //XMFLOAT3 housePos[3];
    XMFLOAT3 objPos = obj_->GetPosition();
    float distance[3];
    

    for (int i = 0; i < 3; i++) {
        for (int y = 0; y < 11; y++) {
            for (int x = 0; x < 11; x++) {
                housePos[i] = floorPos_[houseFloor[i].y][houseFloor[i].x];//�Ƃ̍��W���擾

                //���ݒn�Ɗe�Ƃ܂ŋ����𒲂ׂ�
                distance[i] = abs(housePos[i].x - objPos.x) + abs(housePos[i].z - objPos.z);
            }
        }
    }

    int32_t goalNum;

    //�e�Ƃ܂ł̋������ׂĈ�ԏ������̂��S�[���ɂ���
    if (distance[0] < distance[1] && distance[0] < distance[2]) {
        goalNum = 0;
    }
    else if (distance[1] < distance[0] && distance[1] < distance[2]) {
        goalNum = 1;
    }
    else {
        goalNum = 2;
    }

    goalFloor = houseFloor[goalNum];

    //�Ƃ̂��鏰�͎w��ł��Ȃ�����1�}�X���炷
    XMINT2 shift;
    if ((floorPos_[goalFloor.y][goalFloor.x].x + 5) - objPos.x > 0) {
        shift.x = 1;
        
    }
    else if((floorPos_[goalFloor.y][goalFloor.x].x - 5) - objPos.x < 0){
        shift.x  = -1;
    }
    else{
        shift.x = 0;
    }

    if ((floorPos_[goalFloor.y][goalFloor.x].z + 5) - objPos.z > 0) {
        shift.y = 1;
    }
    else if ((floorPos_[goalFloor.y][goalFloor.x].z - 5) - objPos.z < 0) {
        shift.y = -1;
    }
    else {
        shift.y = 0;
    }

    goalFloor = XMINT2(houseFloor[goalNum].x + shift.x, houseFloor[goalNum].y + shift.y);
}

void Enemy::OnShip(bool isGoal)
{
    if (isOnShip == true) {
        XMFLOAT3 objPos = obj_->GetPosition();

        objPos = { shipPos_.x,3.0f,shipPos_.z };

        obj_->SetPosition(objPos);

        if (isGoal == true) {//�D���ړI�n�ɂ�����
            isOnShip = false;
            isLanding = true;
        }
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

            nowFloor = goal;
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
            isMove = true;
        };
    }
}

void Enemy::Move()
{
    XMFLOAT3 move = { 0.0f, 0.0f, 0.0f };
    XMFLOAT3 pos = obj_->GetPosition();
    float speed = 0.5f;

    //�ŏ��͊C�ɒ���ł��邽�߁A���W���グ��
    if (obj_->GetPosition().y <= routePos_.y) {
        move.y = speed;
    }
    else {
        move.y = 0.0f;
    }

    // �ړ���
    if (routePos_.x < obj_->GetPosition().x) {
        move.x = -speed;
    }
    else if (routePos_.x > obj_->GetPosition().x) {
        move.x = speed;
    }
    else {
        move.x = 0.0f;
    }

    if (routePos_.z < obj_->GetPosition().z) {
        move.z = -speed;
    }
    else if (routePos_.z > obj_->GetPosition().z) {
        move.z = speed;
    }
    else {
        move.z = 0.0f;
    }

    if (isMove == true) {
        //�ړI�n�ɍs���܂ő�����
        if (routePos_.x != obj_->GetPosition().x ||
            routePos_.z != obj_->GetPosition().z) {

            //�ړ�
            pos.x += move.x;
            pos.y += move.y;
            pos.z += move.z;
            obj_->SetPosition(pos);
        }
        //�ړI�n�ɒ�������
        else if (routePos_.x == obj_->GetPosition().x &&
            routePos_.z == obj_->GetPosition().z) {
            //�t���O������
            //isMove = true;
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
    //�D�̏�����
	ship_ = new EnemyShip();
	ship_->Initialize();

    //�G�̏�����
    enemy_ = new Enemy();
    enemy_->Initialize();

    //�����̃��[�g�̏�����
    soldierRoute_ = new SoldierRoute();
    soldierRoute_->Initialize(XMFLOAT3(0, 0, 0), 0);
}

void EnemySoldier::Finalize()
{

}

void EnemySoldier::Update(XMFLOAT3 floorPos[11][11], XMINT2 houseFloor[3], int costMap[11][11])
{   
    
	ship_->Update(floorPos);
    enemy_->Update(ship_->GetPosition(), ship_->GetGoalFloor(), ship_->GetIsGoal(), floorPos, houseFloor, soldierRoute_->GetPosition());

    if (enemy_->GetIsMove() == true) {
        soldierRoute_->Update(enemy_->GetNowFloor(), enemy_->GetGoalFloor(), floorPos, 0, costMap);
    }
}

void EnemySoldier::Draw()
{
	ship_->Draw();
    enemy_->Draw();
}

#pragma endregion