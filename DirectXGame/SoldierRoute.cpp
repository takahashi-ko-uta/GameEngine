#include "SoldierRoute.h"
#include "imgui.h"


void SoldierRoute::Initialize(XMFLOAT3 spawnPos, int soldierNum)
{
	input_ = Input::GetInstance();
    this->spawnPos_ = spawnPos;
    this->soldierNum_ = soldierNum;
    //モデル読み込み
    model_ = Model::LoadFromOBJ("mark");
    //球のモデル初期化
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetScale({ 1.0f,1.0f,1.0f });
    obj_->SetPosition({ spawnPos_.x,10.0f,spawnPos_.z });

    //soldierNumによって色変える(0～3まで)
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

    //スタートとゴールを取得
    this->startFloor_ = startFloor;
    this->goalFloor_ = goalFloor;

    //床の座標を取得
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
        isMove_ = false;
    }
    


   
    if (isMove_ == true) {
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
}

void SoldierRoute::CreateRoute()
{
    //スタートとゴールを保存
    SearchRoute::Cell oldStart = start_;
    SearchRoute::Cell oldGoal = goal_;

    //スタートとゴールを更新
    start_ = SearchRoute::Cell(startFloor_.x, startFloor_.y);
    goal_ = SearchRoute::Cell(goalFloor_.x, goalFloor_.y);

    //ゴールが変更されたらrouteを再検索する
    if (goal_.X != oldGoal.X || goal_.Y != oldGoal.Y) {
        searchRoute_->AStar(start_, goal_);
        isMove_ = true;
    }

    //ルートを取得
    searchRoute_->GetRoute(route_);
}

void SoldierRoute::ChangeSoldierFloor()
{
    //兵隊の床の位置を取得
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 1; x++) {
            //兵隊のx,zと各床のx,zを比べて誤差+-5だったら保存する
            if ((floorPos_[y][x].x + 5) >= obj_->GetPosition().x && (floorPos_[y][x].x - 5) <= obj_->GetPosition().x &&
                (floorPos_[y][x].z + 5) >= obj_->GetPosition().z && (floorPos_[y][x].z - 5) <= obj_->GetPosition().z) {

                soldierFloor_ = { y,x };
            }
        }
    }   
}

void SoldierRoute::ChangeSpawnFloor()
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

void SoldierRoute::Draw()
{
    if (isSelect_ == true) {
        obj_->Draw();
    }   
}
