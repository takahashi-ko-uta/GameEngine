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
    
    //�J����������
    camera_ = new Camera();
    camera_->Initialize();
    camera_->SetEye({ 0, 0, -100 });
    //�I�u�W�F�N�g�S�̂̏�����
    Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height, camera_);

    //�X�v���C�g���ʕ��̏�����
    spriteCommon_ = new SpriteCommon();
    spriteCommon_->Initialize(dxCommon);
    //�e�N�X�`���̃Z�b�g
    spriteCommon_->LoadTexture(0, "texture.png");
    spriteCommon_->LoadTexture(1, "reimu.png");
    //�X�v���C�g������
    sprite_ = new Sprite();
    sprite_->SetTextureIndex(0);
    sprite_->Initialize(spriteCommon_, 0);

    //���f���ǂݍ���
    model_ = Model::LoadFromOBJ("triangle_mat");
    modelCube_ = Model::LoadFromOBJ("cube");
    modelPlane_ = Model::LoadFromOBJ("plane");
    modelSphere = Model::LoadFromOBJ("sphere");

    //�I�u�W�F�N�g����
    objSphere_ = Object3d::Create();
    objPlane_ = Object3d::Create();
    //3D�I�u�W�F�N�g��3D���f�����Ђ��t��
    objSphere_->SetModel(modelSphere);
    objPlane_->SetModel(modelPlane_);
    //3D�I�u�W�F�N�g�̈ʒu���w��
    objSphere_->SetPosition({ 0,0,0 });
    objPlane_->SetPosition({ 0,0,0 });
    //3D�I�u�W�F�N�g�̃X�P�[�����w��
    objSphere_->SetScale({ 5.0f,5.0f ,5.0f });
    objPlane_->SetScale({ 10.0f,10.0f,10.0f });

    //�����蔻��
    sphere.center = XMVectorSet(objSphere_->GetPosition().x, objSphere_->GetPosition().y, objSphere_->GetPosition().z, 1);
    sphere.radius = 5.0f;
    
    plane.normal = XMVectorSet(0, 1, 0, 0);
    plane.distance = objPlane_->GetPosition().y;

    //�T�E���h������
    audio_ = new Audio();
    audio_->Initialize();
    //�T�E���h�ǂݍ���
    audio_->LoadWave("Alarm01.wav");
    //�T�E���h�Đ�
    audio_->PlayWave("Alarm01.wav");
}

void GamePlayScene::Finalize()
{
    //�J�������
    delete camera_;
    //�X�v���C�g���ʕ����
    delete spriteCommon_;

    //�X�v���C�g���
    delete sprite_;
    //�I�u�W�F�N�g���
    delete objSphere_;
    delete objPlane_;
    //���f�����
    delete model_;
    //�I�[�f�B�I���
    audio_->Finalize();
    delete audio_;
}

void GamePlayScene::Update()
{
    //�ړ���
    float moveY = 0.3f;
    
    //���̈ړ�
    XMFLOAT3 spherePos = objSphere_->GetPosition();
    if (input_->PushKey(DIK_Q)) { spherePos.y += moveY; }
    else if (input_->PushKey(DIK_A)) { spherePos.y -= moveY; }
    objSphere_->SetPosition(spherePos);

    //���ʂ̈ړ�
    XMFLOAT3 planePos = objPlane_->GetPosition();
    if (input_->PushKey(DIK_W)) { planePos.y += moveY; }
    else if (input_->PushKey(DIK_S)) { planePos.y -= moveY; }
    objPlane_->SetPosition(planePos);

    //�J�����̈ړ�
    XMFLOAT3 cameraEye = camera_->GetEye();
    if (input_->PushKey(DIK_O)) { cameraEye.y += moveY; }
    else if (input_->PushKey(DIK_L)) { cameraEye.y -= moveY; }
    camera_->SetEye(cameraEye);

    //�����蔻��̍X�V
    sphere.center = XMVectorSet(objSphere_->GetPosition().x, objSphere_->GetPosition().y, objSphere_->GetPosition().z, 1);
    plane.distance = objPlane_->GetPosition().y;

    bool hit = Collision::CheckSphere2Plane(sphere, plane);
    if (hit) {
        ImGui::Text("hit:ture");
    }
    else {
        ImGui::Text("hit:false");
    }

    //ImGui�e�L�X�g
    ImGui::Text("spherePos[Q][A]:%f,%f,%f", spherePos.x, spherePos.y, spherePos.z);
    ImGui::Text("planePos[W][S]:%f,%f,%f", planePos.x, planePos.y, planePos.z);
    ImGui::Text("cameraPos[O][L]:%f,%f,%f", cameraEye.x, cameraEye.y, cameraEye.z);

    //�e�X�̍X�V����
    camera_->Update();
    input_->Update();
    sprite_->Update();
    objSphere_->Update();
    objPlane_->Update();
}

void GamePlayScene::Draw()
{
    //�X�v���C�g�̕`��
    spriteCommon_->PreDraw();
    //sprite_->Draw();
    spriteCommon_->PostDraw();

    //�I�u�W�F�N�g�̕`��
    Object3d::PreDraw(dxCommon_->GetCommandList());
    objSphere_->Draw();
    objPlane_->Draw();
    Object3d::PostDraw();
}
