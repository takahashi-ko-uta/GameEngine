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

    //�J����������
    camera_ = new Camera();
    camera_->Initialize();
    camera_->SetEye({ 0, 0, -100 });

    //�I�u�W�F�N�g�̐ÓI������
    Object3d::StaticInitialize(dxCommon_->GetDevice(), WinApp::window_width, WinApp::window_height, camera_);
    //�p�[�e�B�N���̐ÓI������
    ParticleManager::StaticInitialize(dxCommon_->GetDevice(), WinApp::window_width, WinApp::window_height);

    //�Q�[���p�J����
    gameCamera_ = new GameCamera();
    gameCamera_->Initialize(camera_);

#pragma region �X�v���C�g�֘A
    spriteCommon_ = SpriteCommon::GetInstance();
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
    modelSphere_ = Model::LoadFromOBJ("sphere");
    //���̃��f��������
    objSphere_ = Object3d::Create();
    objSphere_->SetModel(modelSphere_);
    objSphere_->SetScale({ 5.0f,5.0f,5.0f });

    //�X�e�[�W�̏�����
    gameStage_ = new GameStage();
    gameStage_->Initialize();

    //�v���C���[�̏�����
    player_ = new Player();
    player_->Initialize();

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
    audio_ = Audio::GetInstance();
    //�I�[�f�B�I�ǂݍ���
    audio_->LoadWave("Alarm01.wav");
    //�I�[�f�B�I�Đ�
    //audio_->PlayWave("Alarm01.wav");
#pragma endregion  
}

void GamePlayScene::Finalize()
{
    //�J�������
    delete camera_;
    //�Q�[���p�J�������
    delete gameCamera_;
    //�X�v���C�g���ʕ����
    //delete spriteCommon_;
    //�X�v���C�g���
    delete sprite1_;
    delete sprite2_;
    //�I�u�W�F�N�g���
    delete objSphere_;
    //�X�e�[�W���
    gameStage_->Finalize();
    //�v���C���[���
    player_->Finalize();
    //�p�[�e�B�N�����
    delete particle1_;
    delete particle2_;
    //���f�����
    delete modelSphere_;
}

void GamePlayScene::Update()
{
    

    //�J�����̈ړ�
    gameCamera_->Update();

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

    float moniX = input_->GetMouseMonitorPos().x;
    float moniY = input_->GetMouseMonitorPos().y;

    float windowX = input_->GetMouseWindowPos().x;
    float windowY = input_->GetMouseWindowPos().y;

#pragma region ImGui�e�L�X�g
    ImGui::Text("particle[1][2]");
    ImGui::Text("mousePos(X:%f, Y:%f)", moniX, moniY);
    ImGui::Text("mousePos(X:%f, Y:%f)", windowX, windowY);

#pragma endregion
    
    //�X�e�[�W�X�V
    gameStage_->Update();
    //�v���C���[�X�V
    player_->Update();
    //�e�X�̍X�V����
    camera_->Update();
    input_->Update();
    sprite1_->Update();
    sprite2_->Update();
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
    spriteCommon_->PreDraw();   //�X�v���C�g�O����
    sprite1_->Draw();
    sprite2_->Draw();
    spriteCommon_->PostDraw();  //�X�v���C�g�㏈��

    //�I�u�W�F�N�g�̕`��
    Object3d::PreDraw(dxCommon_->GetCommandList()); //�I�u�W�F�N�g�O����

    //�X�e�[�W�`��
    gameStage_->Draw();
    //�v���C���[�`��
    player_->Draw();

    objSphere_->Draw();

    Object3d::PostDraw();                           //�I�u�W�F�N�g�㏈��

    // �p�[�e�B�N���̕`��
    ParticleManager::PreDraw(dxCommon_->GetCommandList());  //�p�[�e�B�N���O����
    particle1_->Draw();
    particle2_->Draw();
    ParticleManager::PostDraw();                            //�p�[�e�B�N���㏈��
}
