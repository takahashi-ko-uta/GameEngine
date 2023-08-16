#include "Soldier.h"
#include "imgui.h"


void Soldier::Initialize(XMFLOAT3 spawnPos, int soldierNum)
{
	input_ = Input::GetInstance();
    this->spawnPos_ = spawnPos;
    //���f���ǂݍ���
    model_ = Model::LoadFromOBJ("Soldier");
    //���̃��f��������
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 1.0f,1.0f,1.0f });
    obj_->SetPosition({ spawnPos_.x,6.0f,spawnPos_.z });

    //soldierNum�ɂ���ĐF�ς���(0�`3�܂�)
    if (soldierNum == 0) { obj_->SetColor({ 1,0,0,1 }); }
    if (soldierNum == 1) { obj_->SetColor({ 0,1,0,1 }); }
    if (soldierNum == 2) { obj_->SetColor({ 0,0,1,1 }); }
    if (soldierNum == 3) { obj_->SetColor({ 1,0,1,1 }); }

    searchRoute_ = new SearchRoute();
    searchRoute_->CreateMap();
    ChangeSpawnFloor();
    //start_ = SearchRoute::Cell(spawnFloor_.x, spawnFloor_.y);
    //goal_ = SearchRoute::Cell(spawnFloor_.x, spawnFloor_.y);

    start_ = SearchRoute::Cell(0, 0);
    goal_ = SearchRoute::Cell(5, 5);
}

void Soldier::Finalize()
{
    
}

void Soldier::Update(XMINT2 startFloor, XMINT2 goalFloor, XMFLOAT3 floorPos[11][11])
{
    //�X�^�[�g�ƃS�[�����擾
    this->startFloor = startFloor;
    this->goalFloor = goalFloor;

    //���̍��W���擾
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            this->floorPos[y][x] = floorPos[y][x];
        }
    }

    Move();

    obj_->Update();
}

void Soldier::Move()
{
    //���[�g�쐬
    CreateRoute();
    //�����̏��̈ʒu���擾
    ChangeSoldierFloor();
    
    for (int i = 0; i < 40; i++) {

    }
    route_[1].x;

    ImGui::Text("count = %d\n", route_[1].x);
}

void Soldier::CreateRoute()
{
    //�X�^�[�g�ƃS�[����ۑ�
    SearchRoute::Cell oldStart = start_;
    SearchRoute::Cell oldGoal = goal_;

    //�X�^�[�g�ƃS�[�����X�V
    start_ = SearchRoute::Cell(startFloor.x, startFloor.y);
    goal_ = SearchRoute::Cell(goalFloor.x, goalFloor.y);

    //�S�[�����ύX���ꂽ��route���Č�������
    if (goal_.X != oldGoal.X || goal_.Y != oldGoal.Y) {
        searchRoute_->AStar(start_, goal_);
    }

    //���[�g���擾
    searchRoute_->GetRoute(route_);
}

void Soldier::ChangeSoldierFloor()
{
    //�����̏��̈ʒu���擾
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 1; x++) {
            //������x,z�Ɗe����x,z���ׂČ덷+-5��������ۑ�����
            if ((floorPos[y][x].x + 5) >= obj_->GetPosition().x && (floorPos[y][x].x - 5) <= obj_->GetPosition().x &&
                (floorPos[y][x].z + 5) >= obj_->GetPosition().z && (floorPos[y][x].z - 5) <= obj_->GetPosition().z) {

                soldierFloor = { y,x };
            }
        }
    }   
}

void Soldier::ChangeSpawnFloor()
{
    //�X�|�[���̏��̈ʒu���擾
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 1; x++) {
            //������x,z�Ɗe����x,z���ׂČ덷+-5��������ۑ�����
            if ((floorPos[y][x].x + 5) >= spawnPos_.x && (floorPos[y][x].x - 5) <= spawnPos_.x &&
                (floorPos[y][x].z + 5) >= spawnPos_.z && (floorPos[y][x].z - 5) <= spawnPos_.z) {

                spawnFloor_ = { y,x };
            }
        }
    }
}

void Soldier::Draw()
{
    obj_->Draw();
}
