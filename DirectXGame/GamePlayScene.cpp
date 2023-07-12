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
    //�I�u�W�F�N�g�̐ÓI������
    Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height, camera_);
    //�p�[�e�B�N���̐ÓI������
    ParticleManager::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
#pragma region �X�v���C�g�֘A
    //�X�v���C�g���ʕ��̏�����
    spriteCommon_ = new SpriteCommon();
    spriteCommon_->Initialize(dxCommon);
    //�e�N�X�`���̃Z�b�g
    spriteCommon_->LoadTexture(0, "texture.png");
    spriteCommon_->LoadTexture(1, "reimu.png");
    //�X�v���C�g������
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
    
#pragma region �I�u�W�F�N�g�֘A
    //���f���ǂݍ���
    modelGround1_ = Model::LoadFromOBJ("ground");
    modelGround2_ = Model::LoadFromOBJ("ground2");
    modelSphere_ = Model::LoadFromOBJ("sphere");

    //�n�ʂ̃I�u�W�F�N�g������
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            //�I�u�W�F�N�g����
            objGround_[i][j] = Object3d::Create();
            //3D�I�u�W�F�N�g��3D���f�����Ђ��t��
            if((i + j) % 2 == 0){
                objGround_[i][j]->SetModel(modelGround1_);
            }
            else {
                objGround_[i][j]->SetModel(modelGround2_);
            }
            //3D�I�u�W�F�N�g�̃X�P�[�����w��
            float size = 5.0f;
            objGround_[i][j]->SetScale({ size,size,size });
  
            //3D�I�u�W�F�N�g�̈ʒu���w��
            objGround_[i][j]->SetPosition({ ((float)i - 2) * size * 2, -2.5f, ((float)j - 2) * size * 2 });
        }
    }

    //���̃��f��������
    objSphere_ = Object3d::Create();
    objSphere_->SetModel(modelSphere_);
    objSphere_->SetScale({ 5.0f,5.0f,5.0f });
    objSphere_->SetPosition({ 0.0f,0.0f,0.0f });

#pragma endregion

    // �p�[�e�B�N������
    particle1_ = ParticleManager::Create();
    particle2_ = ParticleManager::Create();
 
    //�����蔻��
    /*sphere.center = XMVectorSet(objSphere_->GetPosition().x, objSphere_->GetPosition().y, objSphere_->GetPosition().z, 1);
    sphere.radius = 5.0f;
    
    plane.normal = XMVectorSet(0, 1, 0, 0);
    plane.distance = objPlane_->GetPosition().y;*/
    
#pragma region �I�[�f�B�I�֘A
    //�I�[�f�B�I������
    audio_ = new Audio();
    audio_->Initialize();
    //�I�[�f�B�I�ǂݍ���
    audio_->LoadWave("Alarm01.wav");
    //�I�[�f�B�I�Đ�
    audio_->PlayWave("Alarm01.wav");
#pragma endregion  
}

void GamePlayScene::Finalize()
{
    //�J�������
    delete camera_;
    //�X�v���C�g���ʕ����
    delete spriteCommon_;
    //�X�v���C�g���
    delete sprite1_;
    delete sprite2_;
    //�I�u�W�F�N�g���
    delete objSphere_;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            delete objGround_[i][j];
        }
    }
    //�p�[�e�B�N�����
    delete particle1_;
    delete particle2_;
    //���f�����
    delete modelGround1_;
    delete modelGround2_;
    //�I�[�f�B�I���
    audio_->Finalize();
    delete audio_;
}

void GamePlayScene::Update()
{
    //�ړ���
    float move = 0.3f;
    
#pragma region �J�����̈ړ�
    //�J�����̈ړ�
    XMFLOAT3 cameraEye = camera_->GetEye();
    if (input_->PushKey(DIK_UP)) { cameraEye.y += move; }
    else if (input_->PushKey(DIK_DOWN)) { cameraEye.y -= move; }
    if (input_->PushKey(DIK_LEFT)) { cameraEye.x -= move; }
    else if (input_->PushKey(DIK_RIGHT)) { cameraEye.x += move; }
    camera_->SetEye(cameraEye);
#pragma endregion
    
#pragma region �e�I�u�W�F�N�g�̈ړ�
    ////���̈ړ�
    //XMFLOAT3 spherePos = objSphere_->GetPosition();
    //if (input_->PushKey(DIK_Q)) { spherePos.y += move; }
    //else if (input_->PushKey(DIK_A)) { spherePos.y -= move; }
    //objSphere_->SetPosition(spherePos);

    ////���ʂ̈ړ�
    //XMFLOAT3 planePos = objPlane_->GetPosition();
    //if (input_->PushKey(DIK_W)) { planePos.y += move; }
    //else if (input_->PushKey(DIK_S)) { planePos.y -= move; }
    //objPlane_->SetPosition(planePos);

#pragma endregion
    
#pragma region �p�[�e�B�N������ 
    if (input_->PushKey(DIK_1)) {
        particle1_->SetTexture("effect1.png");
        for (int i = 0; i < 100; i++) {
            //X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
            const float md_pos = 10.0f;
            XMFLOAT3 pos{};
            pos.x = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
            pos.y = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
            pos.z = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
            //X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
            const float md_vel = 0.1f;
            XMFLOAT3 vel{};
            vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
            vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
            vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
            //�d�͂Ɍ����Ă�Y�̂�[0.001ff,0]�Ń����_���ɕ��z
            XMFLOAT3 acc{};
            const float md_acc = 0.001f;
            acc.y = -(float)rand() / RAND_MAX * md_acc;
            //�ǉ�
            particle1_->Add(30, pos, vel, acc, 1.0f, 0.0f);
        }
    }
    if (input_->PushKey(DIK_2)) {
        particle1_->SetTexture("effect2.png");
        for (int i = 0; i < 100; i++) {
            //X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
            const float md_pos = 10.0f;
            XMFLOAT3 pos{};
            pos.x = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
            pos.y = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
            pos.z = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
            //X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
            const float md_vel = 0.1f;
            XMFLOAT3 vel{};
            vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
            vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
            vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
            //�d�͂Ɍ����Ă�Y�̂�[0.001ff,0]�Ń����_���ɕ��z
            XMFLOAT3 acc{};
            const float md_acc = 0.001f;
            acc.y = -(float)rand() / RAND_MAX * md_acc;
            //�ǉ�
            particle2_->Add(30, pos, vel, acc, 1.0f, 0.0f);
        }
    }
#pragma endregion 

#pragma region ImGui�e�L�X�g
    ImGui::Text("particle[1][2]");

    //�e�X�̈ʒu
    /*ImGui::Text("spherePos[Q][A]:%f,%f,%f", spherePos.x, spherePos.y, spherePos.z);
    ImGui::Text("planePos[W][S]:%f,%f,%f", planePos.x, planePos.y, planePos.z);*/
    ImGui::Text("cameraEye[arrow]:%f,%f,%f", cameraEye.x, cameraEye.y, cameraEye.z);

    //���ƕ��ʂ͓����������ǂ���
    bool hit = Collision::CheckSphere2Plane(sphere, plane);
    if (hit) { ImGui::Text("hit:ture"); }
    else { ImGui::Text("hit:false"); }
#pragma endregion
    
    //�e�X�̍X�V����
    camera_->Update();
    input_->Update();
    sprite1_->Update();
    sprite2_->Update();
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            objGround_[i][j]->Update();
        }
    }
    objSphere_->Update();
    particle1_->Update();
    particle2_->Update();
    //�����蔻��̍X�V
   /* sphere.center = XMVectorSet(objSphere_->GetPosition().x, objSphere_->GetPosition().y, objSphere_->GetPosition().z, 1);
    plane.distance = objPlane_->GetPosition().y;*/
}

void GamePlayScene::Draw()
{
    //�X�v���C�g�̕`��
    spriteCommon_->PreDraw();
    sprite1_->Draw();
    sprite2_->Draw();
    spriteCommon_->PostDraw();

    //�I�u�W�F�N�g�̕`��
    Object3d::PreDraw(dxCommon_->GetCommandList());
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            objGround_[i][j]->Draw();
        }
    }
    objSphere_->Draw();
    Object3d::PostDraw();

    // �p�[�e�B�N���̕`��
    ParticleManager::PreDraw(dxCommon_->GetCommandList());
    particle1_->Draw();
    particle2_->Draw();
    ParticleManager::PostDraw();
}
