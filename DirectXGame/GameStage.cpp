#include "GameStage.h"
#include "imgui.h"

void GameStage::Initialize()
{
    input = Input::GetInstance();

	//モデル読み込み
	modelGround1_ = Model::LoadFromOBJ("ground");
	modelGround2_ = Model::LoadFromOBJ("ground2");

#pragma region 床オブジェクト初期化
    //地面のオブジェクト初期化
    for (int i = 0; i < stageSize; i++) {
        for (int j = 0; j < stageSize; j++) {
            //オブジェクト生成
            objGround_[i][j] = Object3d::Create();
            //3Dオブジェクトと3Dモデルをひも付け
            if ((i + j) % 2 == 0) {
                objGround_[i][j]->SetModel(modelGround1_);
            }
            else {
                objGround_[i][j]->SetModel(modelGround2_);
            }
            //3Dオブジェクトのスケールを指定
            float size = 5.0f;
            objGround_[i][j]->SetScale({ size,size,size });

            //3Dオブジェクトの位置を指定
            objGround_[i][j]->SetPosition({ ((float)i - stageSize / 2) * size * 2, 0.0f, ((float)j - stageSize / 2) * size * 2 });
        }
    }
#pragma endregion 
    
    for (int i = 0; i < 4; i++){
        startFloor[i] = { 99,99 };
        goalFloor[i] = { 99,99 };
    }


    //兵隊のスポーン位置を設定
    spawnFloor[0] = { 4,4 };
    spawnFloor[1] = { 4,6 };
    spawnFloor[2] = { 6,4 };
    spawnFloor[3] = { 6,6 };
}

void GameStage::Finalize()
{
}

void GameStage::Update()
{
    Select();

    //各地面オブジェクトの更新
    for (int i = 0; i < stageSize; i++) {
        for (int j = 0; j < stageSize; j++) {
            objGround_[i][j]->Update();
        }
    }
}

void GameStage::Select()
{
    //兵隊のいる床を取得
    SetSoldiersFloor();

#pragma region 床の選択
    if (input->TriggerKey(DIK_W)) {
        selectFloor.y += 1;
        if (selectFloor.y == stageSize) { selectFloor.y = 0; }
    }
    if (input->TriggerKey(DIK_S)) {
        selectFloor.y -= 1;
        if (selectFloor.y == -1) { selectFloor.y = stageSize - 1; }
    }
    if (input->TriggerKey(DIK_A)) {
        selectFloor.x -= 1;
        if (selectFloor.x == -1) { selectFloor.x = stageSize - 1; }
    }
    if (input->TriggerKey(DIK_D)) {
        selectFloor.x += 1;
        if (selectFloor.x == stageSize) { selectFloor.x = 0; }
    }
#pragma endregion

    //床の状況に応じて色を変える   
    ChangeFloorColor();
    
    //スペースを押したらスタート地点を設定
    if (input->TriggerKey(DIK_SPACE)) {
        for (int i = 0; i < 4; i++) {
            //スタートは常に更新
            startFloor[i] = soldiersFloor[i];
            //選択した床の上に兵隊がいたら、その兵隊の番号を取得
            if (selectFloor.x == soldiersFloor[i].x && selectFloor.y == soldiersFloor[i].y) {
                selectSoldier = i;
            }
            //番号を取得した兵隊のゴールを更新
            else if (selectSoldier != 5) {
                goalFloor[selectSoldier] = selectFloor;
            }
        }
    }

    //スタート地点、ゴール地点をリセット
    if (input->TriggerKey(DIK_R)) {
        for (int i = 0; i < 4; i++){
            startFloor[i] = {99,99};
            goalFloor[i] = {99,99};
        }
    }

    /*ImGui::Text("soldiers0(X:%.0f, Y:%.0f)", soldiersFloor[0].x, soldiersFloor[0].y);
    ImGui::Text("soldiers1(X:%.0f, Y:%.0f)", soldiersFloor[1].x, soldiersFloor[1].y);
    ImGui::Text("soldiers2(X:%.0f, Y:%.0f)", soldiersFloor[2].x, soldiersFloor[2].y);
    ImGui::Text("soldiers3(X:%.0f, Y:%.0f)", soldiersFloor[3].x, soldiersFloor[3].y);*/


    ImGui::Text("select(X:%.0f, Y:%.0f)", selectFloor.x, selectFloor.y);

    ImGui::Text("selectSoldier: %d", selectSoldier);

    ImGui::Text("S[0](%.0f,%.0f),[1](%.0f,%.0f),[2](%.0f,%.0f),[3](%.0f,%.0f)",
        soldiersFloor[0].x, soldiersFloor[0].y, soldiersFloor[1].x, soldiersFloor[1].y, soldiersFloor[2].x, soldiersFloor[2].y, soldiersFloor[3].x, soldiersFloor[3].y);

    ImGui::Text("S[0](%.0f,%.0f),[1](%.0f,%.0f),[2](%.0f,%.0f),[3](%.0f,%.0f)",
        startFloor[0].x, startFloor[0].y, startFloor[1].x, startFloor[1].y, startFloor[2].x, startFloor[2].y, startFloor[3].x, startFloor[3].y);
    ImGui::Text("G[0](%.0f,%.0f),[1](%.0f,%.0f),[2](%.0f,%.0f),[3](%.0f,%.0f)",
        goalFloor[0].x, goalFloor[0].y, goalFloor[1].x, goalFloor[1].y, goalFloor[2].x, goalFloor[2].y, goalFloor[3].x, goalFloor[3].y);
}

void GameStage::SetSoldiersFloor()
{
    for (int i = 0; i < stageSize; i++) {
        for (int j = 0; j < stageSize; j++) {
            for (int x = 0; x < 4; x++) {
                //兵隊のx,zと各床のx,zを比べて同じだったら保存する
                if (objGround_[i][j]->GetPosition().x == soldiersPos[x].x &&
                    objGround_[i][j]->GetPosition().z == soldiersPos[x].z) {

                    soldiersFloor[x] = { i,j };
                }
            }
        }
    }
}

void GameStage::ChangeFloorColor()
{
    for (int i = 0; i < stageSize; i++) {
        for (int j = 0; j < stageSize; j++) {
            //選択されたオブジェクト(床)を赤にする
            if (i == selectFloor.x && j == selectFloor.y) {
                objGround_[i][j]->SetColor({ 0.5,0,0,1 });
            }
            //スタート地点のオブジェクト(床)を緑にする
            else if (i == startFloor[selectSoldier].x && j == startFloor[selectSoldier].y) {
                objGround_[i][j]->SetColor({ 0,0.5,0,1 });
            }
            //ゴール地点のオブジェクト(床)を青にする
            else if (i == goalFloor[selectSoldier].x && j == goalFloor[selectSoldier].y) {
                objGround_[i][j]->SetColor({ 0,0,0.5,1 });
            }
            //何も指定されてないオブジェクト(床)は元の色
            else {
                objGround_[i][j]->SetColor({ 1,1,1,1 });
            }
        }
    }


    //objGround_[selectFloor.x][selectFloor.y]->SetColor({ 0.5,0,0,1 });
    //for (int i = 0; i < 4; i++) {
    //    objGround_[startFloor[i].x][startFloor[i].y]->SetColor({0,0.5,0,1});
    //    objGround_[goalFloor[i].x][goalFloor[i].y]->SetColor({ 0,0,0.5,1 });
    //}
}

void GameStage::Draw()
{
    //ステージの描画
    for (int i = 0; i < stageSize; i++) {
        for (int j = 0; j < stageSize; j++) {
            objGround_[i][j]->Draw();
        }
    }
}

const XMFLOAT3 GameStage::GetSpawnFloor(int num)
{

    XMFLOAT3 spawnPos;

    int x = spawnFloor[num].x;
    int y = spawnFloor[num].y;

    spawnPos = objGround_[x][y]->GetPosition();
    
    return spawnPos;
}

void GameStage::SetSoldiersPos(XMFLOAT3 soldiersPos[4])
{
    for (int i = 0; i < 4; i++) {
        this->soldiersPos[i] = soldiersPos[i];
    }
}