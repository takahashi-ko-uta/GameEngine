#include "GamePlayScene.h"
#include "DirectXCommon.h"
#include "WinApp.h"
#include "ImGuiManager.h"
#include "imgui.h"
#include "Collision.h"

void GamePlayScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
    this->dxCommon_ = dxCommon;
    this->input_ = input;
    
    //カメラ初期化
    camera_ = new Camera();
    camera_->Initialize();
    camera_->SetEye({ 0, 0, -100 });
    //オブジェクト全体の初期化
    Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height, camera_);

#pragma region スプライト関連
    //スプライト共通部の初期化
    spriteCommon_ = new SpriteCommon();
    spriteCommon_->Initialize(dxCommon);
    //テクスチャのセット
    spriteCommon_->LoadTexture(0, "texture.png");
    spriteCommon_->LoadTexture(1, "reimu.png");
    //スプライト初期化
    sprite1_ = new Sprite();
    sprite1_->SetTextureIndex(0);
    sprite1_->Initialize(spriteCommon_, 0);
    sprite1_->SetSize({ 100,100 });

    sprite2_ = new Sprite();
    sprite2_->SetTextureIndex(1);
    sprite2_->Initialize(spriteCommon_, 1);
    sprite2_->SetSize({ 100,100 });
    sprite2_->SetPosition({ 0,100 });
#pragma endregion 
    
#pragma region オブジェクト関連
    //モデル読み込み
    modelCube_ = Model::LoadFromOBJ("cube");
    modelPlane_ = Model::LoadFromOBJ("plane");
    modelSphere = Model::LoadFromOBJ("sphere");

    //オブジェクト生成
    objSphere_ = Object3d::Create();
    objPlane_ = Object3d::Create();
    objCube_ = Object3d::Create();
    //3Dオブジェクトと3Dモデルをひも付け
    objSphere_->SetModel(modelSphere);
    objPlane_->SetModel(modelPlane_);
    objCube_->SetModel(modelCube_);
    //3Dオブジェクトの位置を指定
    objSphere_->SetPosition({ 0,10,0 });
    objPlane_->SetPosition({ 0,0,0 });
    objCube_->SetPosition({ 0,-10,0 });
    //3Dオブジェクトのスケールを指定
    objSphere_->SetScale({ 5.0f,5.0f ,5.0f });
    objPlane_->SetScale({ 10.0f,10.0f,10.0f });
    objCube_->SetScale({ 5.0f,5.0f,5.0f });
#pragma endregion

    //当たり判定
    sphere.center = XMVectorSet(objSphere_->GetPosition().x, objSphere_->GetPosition().y, objSphere_->GetPosition().z, 1);
    sphere.radius = 5.0f;
    
    plane.normal = XMVectorSet(0, 1, 0, 0);
    plane.distance = objPlane_->GetPosition().y;
    
#pragma region オーディオ関連
    //オーディオ初期化
    audio_ = new Audio();
    audio_->Initialize();
    //オーディオ読み込み
    audio_->LoadWave("Alarm01.wav");
    //オーディオ再生
    audio_->PlayWave("Alarm01.wav");
#pragma endregion  
}

void GamePlayScene::Finalize()
{
    //カメラ解放
    delete camera_;
    //スプライト共通部解放
    delete spriteCommon_;

    //スプライト解放
    delete sprite1_;
    delete sprite2_;
    //オブジェクト解放
    delete objSphere_;
    delete objPlane_;
    delete objCube_;
    //モデル解放
    delete model_;
    //オーディオ解放
    audio_->Finalize();
    delete audio_;
}

void GamePlayScene::Update()
{
    //移動量
    float moveY = 0.3f;
    
    //球の移動
    XMFLOAT3 spherePos = objSphere_->GetPosition();
    if (input_->PushKey(DIK_Q)) { spherePos.y += moveY; }
    else if (input_->PushKey(DIK_A)) { spherePos.y -= moveY; }
    objSphere_->SetPosition(spherePos);

    //平面の移動
    XMFLOAT3 planePos = objPlane_->GetPosition();
    if (input_->PushKey(DIK_W)) { planePos.y += moveY; }
    else if (input_->PushKey(DIK_S)) { planePos.y -= moveY; }
    objPlane_->SetPosition(planePos);

    //カメラの移動
    XMFLOAT3 cameraEye = camera_->GetEye();
    if (input_->PushKey(DIK_O)) { cameraEye.y += moveY; }
    else if (input_->PushKey(DIK_L)) { cameraEye.y -= moveY; }
    camera_->SetEye(cameraEye);

    //球と平面は当たった時にテキスト表示
    bool hit = Collision::CheckSphere2Plane(sphere, plane);
    if (hit) {
        ImGui::Text("hit:ture");
    }
    else {
        ImGui::Text("hit:false");
    }

    //ImGuiテキスト
    ImGui::Text("spherePos[Q][A]:%f,%f,%f", spherePos.x, spherePos.y, spherePos.z);
    ImGui::Text("planePos[W][S]:%f,%f,%f", planePos.x, planePos.y, planePos.z);
    ImGui::Text("cameraPos[O][L]:%f,%f,%f", cameraEye.x, cameraEye.y, cameraEye.z);

    //各々の更新処理
    camera_->Update();
    input_->Update();
    sprite1_->Update();
    sprite2_->Update();
    objSphere_->Update();
    objPlane_->Update();
    objCube_->Update();
    //当たり判定の更新
    sphere.center = XMVectorSet(objSphere_->GetPosition().x, objSphere_->GetPosition().y, objSphere_->GetPosition().z, 1);
    plane.distance = objPlane_->GetPosition().y;
}

void GamePlayScene::Draw()
{
    //スプライトの描画
    spriteCommon_->PreDraw();
    sprite1_->Draw();
    sprite2_->Draw();
    spriteCommon_->PostDraw();

    //オブジェクトの描画
    Object3d::PreDraw(dxCommon_->GetCommandList());
    objSphere_->Draw();
    objPlane_->Draw();
    objCube_->Draw();
    Object3d::PostDraw();
}
