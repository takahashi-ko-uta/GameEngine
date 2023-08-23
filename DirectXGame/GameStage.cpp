#include "GameStage.h"
#include "imgui.h"

void GameStage::Initialize()
{
    input = Input::GetInstance();

	//モデル読み込み
	modelGround1_ = Model::LoadFromOBJ("ground");
	modelGround2_ = Model::LoadFromOBJ("ground2");
    modelSea_ = Model::LoadFromOBJ("sea");
    modelHouse_ = Model::LoadFromOBJ("cube");
       
#pragma region 床オブジェクト初期化
    //地面のオブジェクト初期化
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            //オブジェクト生成
            objFloor_[y][x] = Object3d::Create();
            //3Dオブジェクトと3Dモデルをひも付け
            if ((y + x) % 2 == 0) {
                objFloor_[y][x]->SetModel(modelGround1_);
            }
            else {
                objFloor_[y][x]->SetModel(modelGround2_);
            }
            //3Dオブジェクトのスケールを指定
            float size = 5.0f;
            objFloor_[y][x]->SetScale({ size,size,size });

            //3Dオブジェクトの位置を指定
            if (MapData[y][x] != 0) {
                objFloor_[y][x]->SetPosition({ ((float)y - mapSize / 2) * size * 2, 0.0f, ((float)x - mapSize / 2) * size * 2 });
            }
            else if (MapData[y][x] == 0) {
                objFloor_[y][x]->SetPosition({ 0, 0, -50 });
            }

            if (MapData[y][x] >= 40) {//家
                //家のオブジェクト
                int num = MapData[y][x] - 40;//0～2が入る
                objHouse_[num] = Object3d::Create();
                objHouse_[num]->SetModel(modelHouse_);
                objHouse_[num]->SetScale({ 3.0f,3.0f,3.0f });
                objHouse_[num]->SetPosition({ ((float)y - mapSize / 2) * size * 2, 6.0f, ((float)x - mapSize / 2) * size * 2 });
                hhh[num] = { x,y };
            }
        }
    }
#pragma endregion 
    
    //海のオブジェクト初期化
    objSea_ = Object3d::Create();
    objSea_->SetModel(modelSea_);
    objSea_->SetColor({ 0.0f,0.0f,1.0f,1.0f });
    objSea_->SetScale({ 30.0f,1.0f,30.0f });

    //兵隊のスポーン位置を設定
    spawnFloor[0] = { 4,4 };
    spawnFloor[1] = { 4,6 };
    spawnFloor[2] = { 6,4 };
    spawnFloor[3] = { 6,6 };

    //スタートとゴール初期化
    for (int i = 0; i < 4; i++) {
        startFloor[i] = { spawnFloor[i].x,spawnFloor[i].y};
        goalFloor[i] = { spawnFloor[i].x,spawnFloor[i].y };
    }
}

void GameStage::Finalize()
{
}

void GameStage::Update()
{
    Select();
    SetHouseFloor();
    //各地面オブジェクトの更新
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            floorPos[y][x] = objFloor_[y][x]->GetPosition();
            objFloor_[y][x]->Update();
        }
    }

    for (int i = 0; i < 3; i++) {
        objHouse_[i]->Update();
    }
   
    objSea_->Update();
}

void GameStage::Select()
{
    //兵隊のいる床を取得
    SetSoldiersFloor();

#pragma region 床の選択
    if (input->TriggerKey(DIK_W)) {
        selectFloor.y += 1;
        if (selectFloor.y == mapSize) { selectFloor.y = 0; }
    }
    if (input->TriggerKey(DIK_S)) {
        selectFloor.y -= 1;
        if (selectFloor.y == -1) { selectFloor.y = mapSize - 1; }
    }
    if (input->TriggerKey(DIK_A)) {
        selectFloor.x -= 1;
        if (selectFloor.x == -1) { selectFloor.x = mapSize - 1; }
    }
    if (input->TriggerKey(DIK_D)) {
        selectFloor.x += 1;
        if (selectFloor.x == mapSize) { selectFloor.x = 0; }
    }
#pragma endregion

    //床の状況に応じて色を変える   
    ChangeFloorColor();
    
    //スタートとゴールを決める
    SetStartGoal();


    XMFLOAT3 selectPos = objFloor_[selectFloor.x][selectFloor.y]->GetPosition();

    
    ImGui::Text("select(X:%d, Y:%d)", selectFloor.x, selectFloor.y);
    ImGui::Text("selectPos(X:%.0f, Y:%.0f)", selectPos.x, selectPos.z);
}

void GameStage::SetStartGoal()
{
    //スペースを押したらスタート地点を設定
    if (input->TriggerKey(DIK_SPACE)) {
        int32_t oldNum = selectSoldier;
        for (int i = 0; i < 4; i++) {
            //スタートは常に更新
            startFloor[i] = soldiersFloor[i];
            
            //選択した床の上に兵隊がいたら、その兵隊の番号を取得
            if (selectFloor.x == soldiersFloor[i].x && selectFloor.y == soldiersFloor[i].y) {
                selectSoldier = i;
            }
        }
        //ゴールをセット
        if (selectSoldier != 5 && selectSoldier == oldNum) {
            goalFloor[selectSoldier] = selectFloor;
        }
    }
}

void GameStage::SetSoldiersFloor()
{
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            for (int i = 0; i < 4; i++) {
                //兵隊のx,zと各床のx,zを比べて誤差+-5だったら保存する
                if ((objFloor_[y][x]->GetPosition().x + 5) >= soldiersPos[i].x && (objFloor_[y][x]->GetPosition().x - 5) <= soldiersPos[i].x &&
                    (objFloor_[y][x]->GetPosition().z + 5) >= soldiersPos[i].z && (objFloor_[y][x]->GetPosition().z - 5) <= soldiersPos[i].z) {

                    soldiersFloor[i] = { y,x };
                }
            }
        }
    }
}

void GameStage::SetHouseFloor()
{
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            for (int j = 0; j < 3; j++) {
                if ((objFloor_[y][x]->GetPosition().x + 5) >= objHouse_[j]->GetPosition().x && (objFloor_[y][x]->GetPosition().x - 5) <= objHouse_[j]->GetPosition().x &&
                    (objFloor_[y][x]->GetPosition().z + 5) >= objHouse_[j]->GetPosition().z && (objFloor_[y][x]->GetPosition().z - 5) <= objHouse_[j]->GetPosition().z) {

                    houseFloor_[j] = { y,x };
                }
            }
        }
    }
}

void GameStage::ChangeFloorColor()
{
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            //選択されたオブジェクト(床)を赤にする
            if (y == selectFloor.x && x == selectFloor.y) {
                objFloor_[y][x]->SetColor({ 0.5,0,0,1 });
            }
            //スタート地点のオブジェクト(床)を緑にする
            else if (y == startFloor[selectSoldier].x && x == startFloor[selectSoldier].y) {
                objFloor_[y][x]->SetColor({ 0,0.5,0,1 });
            }
            //ゴール地点のオブジェクト(床)を青にする
            else if (y == goalFloor[selectSoldier].x && x == goalFloor[selectSoldier].y) {
                objFloor_[y][x]->SetColor({ 0,0,0.5,1 });
            }
            //何も指定されてないオブジェクト(床)は元の色
            else {
                objFloor_[y][x]->SetColor({ 1,1,1,1 });
            }
        }
    }
}

void GameStage::CreateCostMap(int mapData[11][11])
{
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            if (this->MapData[y][x] == 1) {
                mapData[y][x] = 1;
            }
            else {
                mapData[y][x] = 0;
            }
        }
    }
}

void GameStage::Draw()
{
    //ステージの描画
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            objFloor_[y][x]->Draw();
        }
    }
    //家の描画
    for (int i = 0; i < 3; i++) {
        objHouse_[i]->Draw();
    }
    //海の描画
    objSea_->Draw();
}

const XMFLOAT3 GameStage::GetSpawnPos(int num)
{

    XMFLOAT3 spawnPos;

    int x = spawnFloor[num].x;
    int y = spawnFloor[num].y;

    spawnPos = objFloor_[x][y]->GetPosition();
    
    return spawnPos;
}

void GameStage::GetFloorPos(XMFLOAT3 floorPos[11][11])
{
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            floorPos[y][x] = this->floorPos[y][x];
        }
    }
}

void GameStage::GetStartPos(XMINT2 startFloor[4])
{
    for (int i = 0; i < 4; i++) {
        startFloor[i] = this->startFloor[i];
    }
}

void GameStage::GetGoalPos(XMINT2 goalFloor[4])
{
    for (int i = 0; i < 4; i++) {
        goalFloor[i] = this->goalFloor[i];
    }
}

void GameStage::GetHouseFloor(XMINT2 houseFloor[3])
{
    for (int i = 0; i < 3; i++) {
        houseFloor[i] = houseFloor_[i];
    }
}

void GameStage::SetSoldiersPos(XMFLOAT3 soldiersPos[4])
{
    for (int i = 0; i < 4; i++) {
        this->soldiersPos[i] = soldiersPos[i];
    }
}