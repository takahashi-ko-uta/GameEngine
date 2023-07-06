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

    //スプライト共通部の初期化
    spriteCommon_ = new SpriteCommon();
    spriteCommon_->Initialize(dxCommon);
    //テクスチャのセット
    spriteCommon_->LoadTexture(0, "texture.png");
    spriteCommon_->LoadTexture(1, "reimu.png");
    //スプライト初期化
    sprite_ = new Sprite();
    sprite_->SetTextureIndex(0);
    sprite_->Initialize(spriteCommon_, 0);

    //モデル読み込み
    model_ = Model::LoadFromOBJ("triangle_mat");
    modelCube_ = Model::LoadFromOBJ("cube");
    modelPlane_ = Model::LoadFromOBJ("plane");
    modelSphere = Model::LoadFromOBJ("sphere");

    //オブジェクト生成
    objSphere_ = Object3d::Create();
    objPlane_ = Object3d::Create();
    //3Dオブジェクトと3Dモデルをひも付け
    objSphere_->SetModel(modelSphere);
    objPlane_->SetModel(modelPlane_);
    //3Dオブジェクトの位置を指定
    objSphere_->SetPosition({ 0,0,0 });
    objPlane_->SetPosition({ 0,0,0 });
    //3Dオブジェクトのスケールを指定
    objSphere_->SetScale({ 5.0f,5.0f ,5.0f });
    objPlane_->SetScale({ 10.0f,10.0f,10.0f });

    //当たり判定
    sphere.center = XMVectorSet(objSphere_->GetPosition().x, objSphere_->GetPosition().y, objSphere_->GetPosition().z, 1);
    sphere.radius = 5.0f;
    
    plane.normal = XMVectorSet(0, 1, 0, 0);
    plane.distance = objPlane_->GetPosition().y;

    //サウンド初期化
    audio_ = new Audio();
    audio_->Initialize();
    //サウンド読み込み
    audio_->LoadWave("Alarm01.wav");
    //サウンド再生
    audio_->PlayWave("Alarm01.wav");
}

void GamePlayScene::Finalize()
{
    //カメラ解放
    delete camera_;
    //スプライト共通部解放
    delete spriteCommon_;

    //スプライト解放
    delete sprite_;
    //オブジェクト解放
    delete objSphere_;
    delete objPlane_;
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

    //当たり判定の更新
    sphere.center = XMVectorSet(objSphere_->GetPosition().x, objSphere_->GetPosition().y, objSphere_->GetPosition().z, 1);
    plane.distance = objPlane_->GetPosition().y;

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
    sprite_->Update();
    objSphere_->Update();
    objPlane_->Update();
}

void GamePlayScene::Draw()
{
    //スプライトの描画
    spriteCommon_->PreDraw();
    //sprite_->Draw();
    spriteCommon_->PostDraw();

    //オブジェクトの描画
    Object3d::PreDraw(dxCommon_->GetCommandList());
    objSphere_->Draw();
    objPlane_->Draw();
    Object3d::PostDraw();
}
