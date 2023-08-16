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
            this->floorPos_[y][x] = floorPos[y][x];
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

    //移動
    int32_t X = route_[routeNum_].x;
    int32_t Y = route_[routeNum_].y;

    XMFLOAT3 move = { 0.0f, 0.0f, 0.0f };
    XMFLOAT3 pos = obj_->GetPosition();

    // 移動量
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

    //route_は99だったらゴールについている
    if (X == 99 && Y == 99) {
        move = { 0,0,0 };
        routeNum_ = 0;
        isMove = false;
    }
    


   
    if (isMove == true) {
        //目的地に行くまで続ける
        if (floorPos_[X][Y].x != pos.x ||
            floorPos_[X][Y].z != pos.z) {


            pos.x += move.x;
            pos.z += move.z;
            obj_->SetPosition(pos);
        }
        //目的地に着いたら
        else if (floorPos_[X][Y].x == pos.x &&
            floorPos_[X][Y].z == pos.z) {
            //次の目的地をセット
            routeNum_++;
        }
    }
    
    /*ImGui::Text("isMove:%d", isMove);
    ImGui::Text("Num:%d", routeNum_);
    ImGui::Text("move(x:%0.2f,z:%0.2f)", move.x, move.z);
    ImGui::Text("pos(x:%0.2f,z:%0.2f)", pos.x, pos.z);
    ImGui::Text("floorPos(x:%0.2f,z:%0.2f)", floorPos_[X][Y].x, floorPos_[X][Y].z);

    for (int i = 0; i < 40; i++) {
        ImGui::Text("x:%d, y:%d", route_[i].x, route_[i].y);
    }*/
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
        isMove = true;
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
            if ((floorPos_[y][x].x + 5) >= obj_->GetPosition().x && (floorPos_[y][x].x - 5) <= obj_->GetPosition().x &&
                (floorPos_[y][x].z + 5) >= obj_->GetPosition().z && (floorPos_[y][x].z - 5) <= obj_->GetPosition().z) {

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
            if ((floorPos_[y][x].x + 5) >= spawnPos_.x && (floorPos_[y][x].x - 5) <= spawnPos_.x &&
                (floorPos_[y][x].z + 5) >= spawnPos_.z && (floorPos_[y][x].z - 5) <= spawnPos_.z) {

                spawnFloor_ = { y,x };
            }
        }
    }
}

void Soldier::Draw()
{
    obj_->Draw();
}
