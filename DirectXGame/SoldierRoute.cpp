#include "SoldierRoute.h"
#include "imgui.h"


void SoldierRoute::Initialize(XMFLOAT3 spawnPos, int soldierNum)
{
	input_ = Input::GetInstance();
    this->spawnPos_ = spawnPos;
    this->soldierNum_ = soldierNum;
    //���f���ǂݍ���
    model_ = Model::LoadFromOBJ("mark");
    //���̃��f��������
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 1.0f,1.0f,1.0f });
    obj_->SetPosition({ spawnPos_.x,10.0f,spawnPos_.z });

    //soldierNum�ɂ���ĐF�ς���(0�`3�܂�)
    if (soldierNum_ == 0) { obj_->SetColor({ 1,0,0,1 }); }
    if (soldierNum_ == 1) { obj_->SetColor({ 0,1,0,1 }); }
    if (soldierNum_ == 2) { obj_->SetColor({ 0,0,1,1 }); }
    if (soldierNum_ == 3) { obj_->SetColor({ 1,0,1,1 }); }

    searchRoute_ = new SearchRoute();
    searchRoute_->CreateMap();
    ChangeSpawnFloor();
    //start_ = SearchRoute::Cell(spawnFloor_.x, spawnFloor_.y);
    //goal_ = SearchRoute::Cell(spawnFloor_.x, spawnFloor_.y);

    start_ = SearchRoute::Cell(0, 0);
    goal_ = SearchRoute::Cell(5, 5);
}

void SoldierRoute::Finalize()
{
    
}

void SoldierRoute::Update(XMINT2 startFloor, XMINT2 goalFloor, XMFLOAT3 floorPos[11][11], int selectSoldier)
{
    if (selectSoldier == soldierNum_) {
        isSelect_ = true;
    }
    else {
        isSelect_ = false;
    }

    //�X�^�[�g�ƃS�[�����擾
    this->startFloor_ = startFloor;
    this->goalFloor_ = goalFloor;

    //���̍��W���擾
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            this->floorPos_[y][x] = floorPos[y][x];
        }
    }

    Move();

    obj_->Update();
}

void SoldierRoute::Move()
{
    //���[�g�쐬
    CreateRoute();
    //�����̏��̈ʒu���擾
    ChangeSoldierFloor();

    //�ړ�
    int32_t X = route_[routeNum_].x;
    int32_t Y = route_[routeNum_].y;

    XMFLOAT3 move = { 0.0f, 0.0f, 0.0f };
    XMFLOAT3 pos = obj_->GetPosition();

    // �ړ���
    if (floorPos_[X][Y].x < pos.x) {
        move.x = -1.0f;
    }
    else if(floorPos_[X][Y].x > pos.x) {
        move.x = 1.0f;
    }
    else {
        move.x = 0.0f;
    }

    if (floorPos_[X][Y].z < pos.z) {
        move.z = -1.0f;
    }
    else if(floorPos_[X][Y].z > pos.z) {
        move.z = 1.0f;
    }
    else {
        move.z = 0.0f;
    }

    //route_��99��������S�[���ɂ��Ă���
    if (X == 99 && Y == 99) {
        move = { 0,0,0 };
        routeNum_ = 0;
        isMove_ = false;
    }
    


   
    if (isMove_ == true) {
        //�ړI�n�ɍs���܂ő�����
        if (floorPos_[X][Y].x != pos.x ||
            floorPos_[X][Y].z != pos.z) {


            pos.x += move.x;
            pos.z += move.z;
            obj_->SetPosition(pos);
        }
        //�ړI�n�ɒ�������
        else if (floorPos_[X][Y].x == pos.x &&
            floorPos_[X][Y].z == pos.z) {
            //���̖ړI�n���Z�b�g
            routeNum_++;
        }
    }
}

void SoldierRoute::CreateRoute()
{
    //�X�^�[�g�ƃS�[����ۑ�
    SearchRoute::Cell oldStart = start_;
    SearchRoute::Cell oldGoal = goal_;

    //�X�^�[�g�ƃS�[�����X�V
    start_ = SearchRoute::Cell(startFloor_.x, startFloor_.y);
    goal_ = SearchRoute::Cell(goalFloor_.x, goalFloor_.y);

    //�S�[�����ύX���ꂽ��route���Č�������
    if (goal_.X != oldGoal.X || goal_.Y != oldGoal.Y) {
        searchRoute_->AStar(start_, goal_);
        isMove_ = true;
    }

    //���[�g���擾
    searchRoute_->GetRoute(route_);
}

void SoldierRoute::ChangeSoldierFloor()
{
    //�����̏��̈ʒu���擾
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 1; x++) {
            //������x,z�Ɗe����x,z���ׂČ덷+-5��������ۑ�����
            if ((floorPos_[y][x].x + 5) >= obj_->GetPosition().x && (floorPos_[y][x].x - 5) <= obj_->GetPosition().x &&
                (floorPos_[y][x].z + 5) >= obj_->GetPosition().z && (floorPos_[y][x].z - 5) <= obj_->GetPosition().z) {

                soldierFloor_ = { y,x };
            }
        }
    }   
}

void SoldierRoute::ChangeSpawnFloor()
{
    //�X�|�[���̏��̈ʒu���擾
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 1; x++) {
            //������x,z�Ɗe����x,z���ׂČ덷+-5��������ۑ�����
            if ((floorPos_[y][x].x + 5) >= spawnPos_.x && (floorPos_[y][x].x - 5) <= spawnPos_.x &&
                (floorPos_[y][x].z + 5) >= spawnPos_.z && (floorPos_[y][x].z - 5) <= spawnPos_.z) {

                spawnFloor_ = { y,x };
            }
        }
    }
}

void SoldierRoute::Draw()
{
    if (isSelect_ == true) {
        obj_->Draw();
    }   
}
