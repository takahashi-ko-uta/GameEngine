#include "Soldier.h"
#include "imgui.h"


void Soldier::Initialize(XMFLOAT3 spawnPos, int soldierNum)
{
	input_ = Input::GetInstance();
    this->spawnPos_ = spawnPos;
    //モデル読み込み
    model_ = Model::LoadFromOBJ("Soldier");
    //球のモデル初期化
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 1.0f,1.0f,1.0f });
    obj_->SetPosition({ spawnPos_.x,6.0f,spawnPos_.z });

    //soldierNumによって色変える(0～3まで)
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
    //スタートとゴールを取得
    this->startFloor = startFloor;
    this->goalFloor = goalFloor;

    //床の座標を取得
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
    //ルート作成
    CreateRoute();
    //兵隊の床の位置を取得
    ChangeSoldierFloor();
    
    for (int i = 0; i < 40; i++) {

    }
    route_[1].x;

    ImGui::Text("count = %d\n", route_[1].x);
}

void Soldier::CreateRoute()
{
    //スタートとゴールを保存
    SearchRoute::Cell oldStart = start_;
    SearchRoute::Cell oldGoal = goal_;

    //スタートとゴールを更新
    start_ = SearchRoute::Cell(startFloor.x, startFloor.y);
    goal_ = SearchRoute::Cell(goalFloor.x, goalFloor.y);

    //ゴールが変更されたらrouteを再検索する
    if (goal_.X != oldGoal.X || goal_.Y != oldGoal.Y) {
        searchRoute_->AStar(start_, goal_);
    }

    //ルートを取得
    searchRoute_->GetRoute(route_);
}

void Soldier::ChangeSoldierFloor()
{
    //兵隊の床の位置を取得
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 1; x++) {
            //兵隊のx,zと各床のx,zを比べて誤差+-5だったら保存する
            if ((floorPos[y][x].x + 5) >= obj_->GetPosition().x && (floorPos[y][x].x - 5) <= obj_->GetPosition().x &&
                (floorPos[y][x].z + 5) >= obj_->GetPosition().z && (floorPos[y][x].z - 5) <= obj_->GetPosition().z) {

                soldierFloor = { y,x };
            }
        }
    }   
}

void Soldier::ChangeSpawnFloor()
{
    //スポーンの床の位置を取得
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 1; x++) {
            //兵隊のx,zと各床のx,zを比べて誤差+-5だったら保存する
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
