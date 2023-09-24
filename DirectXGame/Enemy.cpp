#include "Enemy.h"
#include "imgui.h"
#include <iostream>     
#include <ctime>        
#include <cstdlib> 

#pragma region EnemyNormal
void EnemyNormal::Initialize(int soldierNum)
{
    this->soldierNum_ = soldierNum;
    //���f���ǂݍ���
    model_ = Model::LoadFromOBJ("Soldier");
    //���̃��f��������
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 0.5f,0.5f,0.5f });
    obj_->SetColor({ 0,0,0,1 });
}

void EnemyNormal::Finalize()
{

}

void EnemyNormal::Update(XMFLOAT3 pos)
{
    //���[�_�[�̈ʒu�ۑ�
    leaderPos = pos;
    XMFLOAT3 objPos = obj_->GetPosition();

    switch (soldierNum_)
    {
    case 0://�E
        goalPos = { leaderPos.x + 3.0f,leaderPos.y,leaderPos.z };
        break;
    case 1://��
        goalPos = { leaderPos.x - 3.0f,leaderPos.y,leaderPos.z };
        break;
    case 2://��
        goalPos = { leaderPos.x,leaderPos.y,leaderPos.z - 3.0f };
        break;
    case 3://��
        goalPos = { leaderPos.x,leaderPos.y,leaderPos.z + 3.0f };
        break;
    case 4://�E��
        goalPos = { leaderPos.x + 3.0f,leaderPos.y,leaderPos.z + 3.0f };
        break;
    case 5://�E��
        goalPos = { leaderPos.x + 3.0f,leaderPos.y,leaderPos.z - 3.0f };
        break;
    case 6://����
        goalPos = { leaderPos.x - 3.0f,leaderPos.y,leaderPos.z + 3.0f };
        break;
    case 7://����
        goalPos = { leaderPos.x - 3.0f,leaderPos.y,leaderPos.z - 3.0f };
        break;
    }

    obj_->SetPosition(goalPos);
    obj_->Update();
}

void EnemyNormal::Draw()
{
    obj_->Draw();
}
#pragma endregion

#pragma region EnemyLeader
void EnemyLeader::Initialize()
{
    //���f���ǂݍ���
    model_ = Model::LoadFromOBJ("Soldier");
    //���̃��f��������
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetPosition({ 90,-50,90 });//�ŏ��͌����Ȃ��Ƃ����
    obj_->SetScale({ 0.5f,0.5f,0.5f });
    obj_->SetColor({ 0,0,0,1 });

    enemyRoute_ = new SearchRoute();
}

void EnemyLeader::Finalize()
{

}

void EnemyLeader::Update(XMFLOAT3 pos, XMINT2 goal, bool isGoal, XMFLOAT3 floorPos[11][11], int costMap[11][11],XMINT2 houseFloor[3])
{
    shipPos_ = pos;//�D�̍��W��ۑ�
    
    for (int i = 0; i < 3; i++) {
        this->houseFloor_[i] = houseFloor[i];
    }
    
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            this->floorPos_[y][x] = floorPos[y][x];//���̍��W�ۑ�
            this->costMap_[y][x] = costMap[y][x];

            //���̍��W��x,z�Ɗe����x,z���ׂČ덷+-5��������ۑ�����
            if ((floorPos_[y][x].x + 5) >= obj_->GetPosition().x && (floorPos_[y][x].x - 5) <= obj_->GetPosition().x &&
                (floorPos_[y][x].z + 5) >= obj_->GetPosition().z && (floorPos_[y][x].z - 5) <= obj_->GetPosition().z) {

                nowFloor = { y,x };//�����鏰
            }
        }
    }

   
    //�D�̏�ɂ���Ƃ�
    OnShip(isGoal);

    //�D���痤�֏オ��
    Landing(goal);

    

    obj_->Update();
    ImGui::Text("aaaa:%d", aaaa);
    ImGui::Text("start:(%d, %d)", start_.X, start_.Y);
    ImGui::Text("goal :(%d, %d)", goal_.X, goal_.Y);

    for (int i = 0; i < 10; i++) {
        ImGui::Text("route[%d]:(%d, %d)", i, route[i].x, route[i].y);
    }

    ImGui::Text("-----------------------------------------");
}

void EnemyLeader::OnShip(bool isGoal)
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

void EnemyLeader::Landing(XMINT2 goal)
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

            CreateRoute();
            //�t���O������
            isLanding = false;
            isMove = true;
        };
    }
}

void EnemyLeader::SearchHouse()
{
    //�S�[��(��ԋ߂���)��T��
    XMFLOAT3 objPos = obj_->GetPosition();
    float distance[3];

#pragma region �e�Ƃ܂ł̋����𒲂ׂ�
    //�e�Ƃ܂ł̋����𒲂ׂ�
    for (int i = 0; i < 3; i++) {
        housePos[i] = floorPos_[houseFloor_[i].y][houseFloor_[i].x];//�Ƃ̍��W���擾

        //������ۑ�
        distance[i] = Distance(objPos.x, objPos.z, housePos[i].x, housePos[i].z);
    }

    if (distance[0] <= distance[1] && distance[0] <= distance[2]) {
        goalHouseNum = 0;
    }
    else if (distance[1] <= distance[0] && distance[1] <= distance[2]) {
        goalHouseNum = 1;
    }
    else if (distance[2] <= distance[0] && distance[2] <= distance[1]) {
        goalHouseNum = 2;
    }

    //goalHouseNum = 0;
#pragma endregion

#pragma region �Ƃ̂��鏰�͎w��ł��Ȃ�����1�}�X���炷
    //�Ƃ̂��鏰�͎w��ł��Ȃ�����1�}�X���炷
    XMINT2 shift;
    if ((floorPos_[goalFloor.y][goalFloor.x].x) - objPos.x < 0) {
        shift.x = 1;

    }
    else if ((floorPos_[goalFloor.y][goalFloor.x].x) - objPos.x > 0) {
        shift.x = -1;
    }
    else {
        shift.x = 0;
    }

    if ((floorPos_[goalFloor.y][goalFloor.x].z) - objPos.z < 0) {
        shift.y = 1;
    }
    else if ((floorPos_[goalFloor.y][goalFloor.x].z) - objPos.z > 0) {
        shift.y = -1;
    }
    else {
        shift.y = 0;
    }
#pragma endregion

    
    //�S�[���ɕۑ�
    goalFloor = { houseFloor_[goalHouseNum].x + shift.x,houseFloor_[goalHouseNum].y + shift.y };

    //goalFloor = houseFloor_[goalHouseNum];



    //goalFloor = { 5,4 };
}

void EnemyLeader::CreateRoute()
{
    //��ԋ߂��Ƃ�T��
    SearchHouse();

    //�}�b�v���ύX���ꂽ���蒼��
    if (isChangeMap == true) {
        enemyRoute_->CreateMap(costMap_);
        isChangeMap = false;
    }

    //�X�^�[�g�ƃS�[����ۑ�
    SearchRoute::Cell oldStart = start_;
    SearchRoute::Cell oldGoal = goal_;

    //SearchHouse();

    //�X�^�[�g�ƃS�[�����X�V
    start_ = SearchRoute::Cell(nowFloor.x, nowFloor.y);
    goal_ = SearchRoute::Cell(goalFloor.x, goalFloor.y);

    //�S�[�����ύX���ꂽ��route���Č�������
    if (goal_.X != oldGoal.X || goal_.Y != oldGoal.Y) {
        
        enemyRoute_->AStar(start_, goal_);
        aaaa++;
    }

    //���[�g���擾
    enemyRoute_->GetRoute(route);
}

float EnemyLeader::Distance(float p1X, float p1Y, float p2X, float p2Y)
{
    return sqrt(pow(p2X - p1X, 2) + pow(p2Y - p1Y, 2));
}

void EnemyLeader::Draw()
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
    //���[�_�[
    leader_ = new EnemyLeader();
    leader_->Initialize();
    //���̑�
    for (int i = 0; i < 8; i++) {
        normal_[i] = new EnemyNormal();
        normal_[i]->Initialize(i);
    }
}

void EnemySoldier::Finalize()
{

}

void EnemySoldier::Update(XMFLOAT3 floorPos[11][11], XMINT2 houseFloor[3], int costMap[11][11])
{   
    ship_->SetIsStart(isStart_);
	ship_->Update(floorPos);
    leader_->Update(ship_->GetPosition(), ship_->GetGoalFloor(), ship_->GetIsGoal(), floorPos, costMap, houseFloor);
    for (int i = 0; i < 8; i++) {
        normal_[i]->Update(leader_->GetPosition());
    }
}

void EnemySoldier::Draw()
{
	ship_->Draw();
    leader_->Draw();
    for (int i = 0; i < 8; i++) {
        normal_[i]->Draw();
    }
}

#pragma endregion

#pragma region Enemy
void Enemy::Initialize()
{
    for (int i = 0; i < 5; i++) {
        soldier[i] = new EnemySoldier();
        soldier[i]->Initialize();
    }
    
}

void Enemy::Finalize()
{

}

void Enemy::Update(XMFLOAT3 floorPos[11][11], XMINT2 houseFloor[3], int costMap[11][11])
{
    //�X�|�[��
    Spawn();

    //1�E�F�[�u�I�������(5�Ǖ��̓G��|������)�D�ƓG������


    for (int i = 0; i < 5; i++) {
        /*soldier[i]->SetIsSpawn(isSpawnShip[i]);*/
        soldier[i]->Update(floorPos, houseFloor, costMap);
    }

    /*ImGui::Text("num:%d", num);
    ImGui::Text("enemyNum:%d", enemyNum);   */
}

void Enemy::Spawn()
{
    float timer = 200;

    if (isSpawn == true) {
        spawnTime++;

        if (spawnTime >= timer) {//���ԂɂȂ�����
            spawnTime = 0;
            //�G(Normal)�̐������߂�2�`8
            std::srand(time(nullptr));//��������
            enemyNum = rand() % 7 + 2;
            isStartShip[num] = true;//�D���X�|�[��������
            soldier[num]->SetIsStart(isStartShip[num]);
            num++;
           
            //�D��5�ǂ�������
            if (num == 5) {
                num = 0;
                isSpawn = false;
            }
        }
    }
}

void Enemy::Draw()
{
    for (int i = 0; i < 5; i++) {
        soldier[i]->Draw();
    }
}
#pragma endregion

