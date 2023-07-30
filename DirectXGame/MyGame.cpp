#include "MyGame.h"


void MyGame::Initialize()
{
    //基盤システムの初期化
    Framework::Initialize();

    //最初のシーンを初期化
    //imGuiManager初期化
    imGuiManager = new ImGuiManager();
    imGuiManager->Initialize(winApp, dxCommon);

    //シーンの初期化
    scene = new GamePlayScene();
    scene->Initialize();
}

void MyGame::Finalize()
{
    //最初のシーンの終了
    imGuiManager->Finalize();
    delete imGuiManager;

    //シーンの終了処理
    scene->Finalize();
  
    //基盤システムの終了
    Framework::Finalize();
}

void MyGame::Update()
{
    //基盤システムの更新
    Framework::Update();

    //最初のシーンの更新
  
    imGuiManager->Begin();
    //シーンの毎フレーム処理
    scene->Update();

    //ImGuiのデモウィンドウ表示
    //ImGui::ShowDemoWindow();
    imGuiManager->End();
}

void MyGame::Draw()
{
    //描画前処理
    dxCommon->PreDraw();

    //シーンの描画
    scene->Draw();

    imGuiManager->Draw();

    //描画後処理
    dxCommon->PostDraw();
}