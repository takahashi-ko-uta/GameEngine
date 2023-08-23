#include "EnemyShip.h"
#include "imgui.h"
#include <iostream>     
#include <ctime>        
#include <cstdlib>      

#define PI 3.14159265359

void EnemyShip::Initialize()
{
    this->input_ = Input::GetInstance();
    //モデル読み込み
    model_ = Model::LoadFromOBJ("boat");
    //球のモデル初期化
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetPosition({ 0.0f,3.0f,0.0f });
    obj_->SetScale({ 1.5f,1.5f,1.5f });
    
}

void EnemyShip::Finalize()
{

}

void EnemyShip::Update(XMFLOAT3 floorPos[11][11])
{
    //乱数生成
    std::srand(time(nullptr));

    //各床の座標を取得
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            this->floorPos_[y][x] = floorPos[y][x];
        }
    }


    //船のゴールを決める
    CreateGoal(floorPos);
    //着陸までの動き
    Move();

    obj_->Update();
}

void EnemyShip::CreateGoal(XMFLOAT3 floorPos[11][11])
{
    //スポーンフラグが立ったら、
    if (isSpawn == true) {
        direction = rand() % 4;     //スポーンする方向を決める
        floorNum = rand() % 11;     //着陸する床
        randomPos = rand() % 61 - 30;//スタートの座標
        isSpawn = false;            //フラグを切る
        isSelect = true;            //ゴールを決める
    }

    switch (direction) {
    case 0://+x方向
        obj_->SetRotation({ 0.0f,270.0f,0.0f });        //モデル方向変更
        startPos = { 250.0f,-10.0f,randomPos };         //スタート位置
        goalFloor = XMINT2(10, floorNum);               //着陸する床
        goalPos = floorPos_[goalFloor.x][goalFloor.y];  //着陸する座標
        goalPos = { goalPos.x + 13, 0.0f,goalPos.z };   //↑のままだと床にめり込むため調整
        break;

    case 1://-x方向
        obj_->SetRotation({ 0.0f,90.0f,0.0f });
        startPos = { -250.0f,-10.0f,randomPos };
        goalFloor = XMINT2(0, floorNum);
        goalPos = floorPos_[goalFloor.x][goalFloor.y];
        goalPos = { goalPos.x -13, 0.0f,goalPos.z };
        break;

    case 2://+z方向
        obj_->SetRotation({ 0.0f,180.0f,0.0f });
        startPos = { randomPos,-10.0f,250.0f };
        goalFloor = XMINT2(floorNum, 10);
        goalPos = floorPos_[goalFloor.x][goalFloor.y];
        goalPos = { goalPos.x, 0.0f,goalPos.z + 13 };
        break;

    case 3://-z方向
        obj_->SetRotation({ 0.0f,0.0f,0.0f });
        startPos = { randomPos,-10.0f,-250.0f };
        goalFloor = XMINT2(floorNum, 0);
        goalPos = floorPos_[goalFloor.x][goalFloor.y];
        goalPos = { goalPos.x, 0.0f,goalPos.z - 13 };
        break;
    }

    if (isSelect == true) {
        obj_->SetPosition(startPos);
        isSelect = false;
        isMove = true;
    }
}

void EnemyShip::Move()
{
    XMFLOAT3 move = { 0.0f, 0.0f, 0.0f };
    XMFLOAT3 pos = obj_->GetPosition();
    float speed = 0.5f;
  
    //最初は海に沈んでいるため、座標を上げる
    if (obj_->GetPosition().y <= goalPos.y) {
        move.y = speed;
    }
    else{
        move.y = 0.0f;
    }

    // 移動量
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

    if (isMove == true) {
        //目的地に行くまで続ける
        if (goalPos.x != obj_->GetPosition().x ||
            goalPos.z != obj_->GetPosition().z) {

            //移動
            pos.x += move.x;
            pos.y += move.y;
            pos.z += move.z;

            num++;

            obj_->SetPosition(pos);
        }
        //目的地に着いたら
        else if (goalPos.x == obj_->GetPosition().x &&
            goalPos.z == obj_->GetPosition().z) {
            //フラグを消す
            isMove = false;
            isGoal = true;
        };
    }
}

void EnemyShip::Draw()
{
    obj_->Draw();
}
