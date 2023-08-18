#include "GameStage.h"
#include "imgui.h"

void GameStage::Initialize()
{
    input = Input::GetInstance();

	//モデル読み込み
	modelGround1_ = Model::LoadFromOBJ("ground");
	modelGround2_ = Model::LoadFromOBJ("ground2");
    modelSea_ = Model::LoadFromOBJ("sea");

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
            if (MapData[y][x] == 1) {
                objFloor_[y][x]->SetPosition({ ((float)y - mapSize / 2) * size * 2, 0.0f, ((float)x - mapSize / 2) * size * 2 });
            }
            else if (MapData[y][x] == 0) {
                objFloor_[y][x]->SetPosition({ 0, 0, -50 });
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

    //各地面オブジェクトの更新
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            floorPos[y][x] = objFloor_[y][x]->GetPosition();
            objFloor_[y][x]->Update();
        }
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

    ImGui::Text("selectSoldier: %d", selectSoldier);

    ImGui::Text("Soldiers[0](%d,%d),[1](%d,%d),[2](%d,%d),[3](%d,%d)",
        soldiersFloor[0].x, soldiersFloor[0].y, soldiersFloor[1].x, soldiersFloor[1].y, soldiersFloor[2].x, soldiersFloor[2].y, soldiersFloor[3].x, soldiersFloor[3].y);

    ImGui::Text("S[0](%d,%d),[1](%d,%d),[2](%d,%d),[3](%d,%d)",
        startFloor[0].x, startFloor[0].y, startFloor[1].x, startFloor[1].y, startFloor[2].x, startFloor[2].y, startFloor[3].x, startFloor[3].y);
    ImGui::Text("G[0](%d,%d),[1](%d,%d),[2](%d,%d),[3](%d,%d)",
        goalFloor[0].x, goalFloor[0].y, goalFloor[1].x, goalFloor[1].y, goalFloor[2].x, goalFloor[2].y, goalFloor[3].x, goalFloor[3].y);
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

void GameStage::Draw()
{
    //ステージの描画
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            objFloor_[y][x]->Draw();
        }
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

void GameStage::GetMapData(int mapData[11][11], int mapSizeX, int mapSizeY)
{
    mapSizeX = this->mapSize;
    mapSizeY = this->mapSize;

    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            mapData[y][x] = MapData[y][x];
        }
    }
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

void GameStage::SetSoldiersPos(XMFLOAT3 soldiersPos[4])
{
    for (int i = 0; i < 4; i++) {
        this->soldiersPos[i] = soldiersPos[i];
    }
}