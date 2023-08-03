#include "GameStage.h"
#include "imgui.h"

void GameStage::Initialize()
{
    input = Input::GetInstance();

	//モデル読み込み
	modelGround1_ = Model::LoadFromOBJ("ground");
	modelGround2_ = Model::LoadFromOBJ("ground2");

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
            objGround_[i][j]->SetPosition({ ((float)i - stageSize/2) * size * 2, -2.5f, ((float)j - stageSize/2) * size * 2 });
        }
    }
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
   
    
    for (int i = 0; i < stageSize; i++) {
        for (int j = 0; j < stageSize; j++) {
            //選択されたオブジェクト(床)を赤にする
            if (i == selectFloor.x && j == selectFloor.y) {
                objGround_[i][j]->SetColor({ 0.5,0,0,1 });
            }
            //スタート地点のオブジェクト(床)を緑にする
            else if (i == startFloor.x && j == startFloor.y) {
                objGround_[i][j]->SetColor({ 0,0.5,0,1 });
            }
            //ゴール地点のオブジェクト(床)を青にする
            else if (i == goalFloor.x && j == goalFloor.y) {
                objGround_[i][j]->SetColor({ 0,0,0.5,1 });
            }
            //何も指定されてないオブジェクト(床)は元の色
            else {
                objGround_[i][j]->SetColor({ 1,1,1,1 });
            }
        }
    }

    //スペースを押したらスタート地点を設定
    if (input->TriggerKey(DIK_SPACE)) {
        //スタート地点がまだ決まってなかったらスタート地点を設定
        if (startFloor.x > stageSize) {
            startFloor = selectFloor;
        }

        //もしスタート地点が既に決まってらゴール地点を設定
        if (startFloor.x < stageSize) {
            goalFloor = selectFloor;
        }
    }

    //スタート地点、ゴール地点をリセット
    if (input->TriggerKey(DIK_R)) {
        startFloor = { 99,99 };
        goalFloor = { 99,99 };
    }

  
    ImGui::Text("select(X:%.0f, Y:%.0f)", selectFloor.x, selectFloor.y);
    ImGui::Text(" start(X:%.0f, Y:%.0f)", startFloor.x, startFloor.y);
    ImGui::Text("  goal(X:%.0f, Y:%.0f)", goalFloor.x, goalFloor.y);
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
