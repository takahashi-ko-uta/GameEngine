#include "GamePlayScene.h"
#include "DirectXCommon.h"
#include "WinApp.h"
#include "ImGuiManager.h"
#include "imgui.h"
#include "Collision.h"

void GamePlayScene::Initialize()
{
    dxCommon_ = DirectXCommon::GetInstance();
    input_ = Input::GetInstance();

    //カメラ初期化
    camera_ = new Camera();
    camera_->Initialize();
    camera_->SetEye({ 0, 0, -100 });

    //オブジェクトの静的初期化
    Object3d::StaticInitialize(dxCommon_->GetDevice(), WinApp::window_width, WinApp::window_height, camera_);
    //パーティクルの静的初期化
    ParticleManager::StaticInitialize(dxCommon_->GetDevice(), WinApp::window_width, WinApp::window_height);

    //ゲーム用カメラ
    gameCamera_ = new GameCamera();
    gameCamera_->Initialize(camera_);

#pragma region スプライト関連
    spriteCommon_ = SpriteCommon::GetInstance();
   
    gameSprite_ = new GameSprite();
    gameSprite_->Initialize();
#pragma endregion 
    
#pragma region オブジェクト関連
    //モデル読み込み
    modelSphere_ = Model::LoadFromOBJ("sphere");
    //球のモデル初期化
    objSphere_ = Object3d::Create();
    objSphere_->SetModel(modelSphere_);
    objSphere_->SetScale({ 5.0f,5.0f,5.0f });

    //ステージの初期化
    gameStage_ = new GameStage();
    gameStage_->Initialize();

    //兵隊の初期化
    for (int i = 0; i < 4; i++) {
        soldier_[i] = new Soldier();
        soldier_[i]->Initialize(gameStage_->GetSpawnFloor(i),i);
    }

    //プレイヤーの初期化
    //player_ = new Player();
    //player_->Initialize(camera_);

#pragma endregion

    //当たり判定
    /*sphere.center = XMVectorSet(objSphere_->GetPosition().x, objSphere_->GetPosition().y, objSphere_->GetPosition().z, 1);
    sphere.radius = 5.0f;
    
    plane.normal = XMVectorSet(0, 1, 0, 0);
    plane.distance = objPlane_->GetPosition().y;*/
    
#pragma region オーディオ関連
    audio_ = Audio::GetInstance();
    //オーディオ読み込み
    audio_->LoadWave("Alarm01.wav");
    //オーディオ再生
    //audio_->PlayWave("Alarm01.wav");
#pragma endregion  
}

void GamePlayScene::Finalize()
{
    //カメラ解放
    delete camera_;
    //ゲーム用カメラ解放
    delete gameCamera_;
    //オブジェクト解放
    delete objSphere_;
    //ステージ解放
    gameStage_->Finalize();
    //プレイヤー解放
    //player_->Finalize();
    //モデル解放
    delete modelSphere_;
}

void GamePlayScene::Update()
{
    //カメラの移動
    gameCamera_->Update();
    //camera_->SetTarget({ 0.0f,0.0f,0.0f });
    //camera_->SetEye({ 1.0f,250.0f,0.0f });
    //camera_->SetEye({ 0.0f,5.0f,-80.0f });

#pragma region 兵隊関連
    //兵隊の位置をsoldiersPosにまとめる
    for (int i = 0; i < 4; i++) {
        soldiersPos_[i] = soldier_[i]->GetPosition();
    }

    //スタートとゴールを取得する
    gameStage_->GetStartPos(startFloor);
    gameStage_->GetGoalPos(goalFloor);

    //床の座標を取得
    gameStage_->GetFloorPos(floorPos);

    gameStage_->SetSoldiersPos(soldiersPos_);

#pragma endregion
    

   
    
#pragma region ImGuiテキスト
    
#pragma endregion
    
    gameSprite_->Update();
    //ステージ更新
    gameStage_->Update();
    //各兵隊の更新
    for (int i = 0; i < 4; i++) {
        soldier_[i]->Update(startFloor[i], goalFloor[i], floorPos);
    }
    //プレイヤー更新
    //player_->Update();
    //各々の更新処理
    camera_->Update();
    input_->Update();
    objSphere_->Update();

    //当たり判定の更新
   /* sphere.center = XMVectorSet(objSphere_->GetPosition().x, objSphere_->GetPosition().y, objSphere_->GetPosition().z, 1);
    plane.distance = objPlane_->GetPosition().y;*/
}

void GamePlayScene::Draw()
{
    //スプライトの描画
    spriteCommon_->PreDraw();   //スプライト前処理
    gameSprite_->Draw();
    //player_->DrawUI();
    spriteCommon_->PostDraw();  //スプライト後処理

    //オブジェクトの描画
    Object3d::PreDraw(dxCommon_->GetCommandList()); //オブジェクト前処理

    //ステージ描画
    gameStage_->Draw();
    //プレイヤー描画
    //player_->Draw();
    //各兵隊の更新
    for (int i = 0; i < 4; i++) {
        soldier_[i]->Draw();
    }

    objSphere_->Draw();

    Object3d::PostDraw();                           //オブジェクト後処理

    // パーティクルの描画
    ParticleManager::PreDraw(dxCommon_->GetCommandList());  //パーティクル前処理

    ParticleManager::PostDraw();                            //パーティクル後処理
}
