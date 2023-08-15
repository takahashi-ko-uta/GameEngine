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
   
    gameSprite_ = new GameSprite();
    gameSprite_->Initialize();
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

    //�����̏�����
    for (int i = 0; i < 4; i++) {
        soldier_[i] = new Soldier();
        soldier_[i]->Initialize(gameStage_->GetSpawnFloor(i),i);
    }

    //�v���C���[�̏�����
    //player_ = new Player();
    //player_->Initialize(camera_);

#pragma endregion

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
    //�I�u�W�F�N�g���
    delete objSphere_;
    //�X�e�[�W���
    gameStage_->Finalize();
    //�v���C���[���
    //player_->Finalize();
    //���f�����
    delete modelSphere_;
}

void GamePlayScene::Update()
{
    //�J�����̈ړ�
    gameCamera_->Update();
    //camera_->SetTarget({ 0.0f,0.0f,0.0f });
    //camera_->SetEye({ 1.0f,250.0f,0.0f });
    //camera_->SetEye({ 0.0f,5.0f,-80.0f });

#pragma region �����֘A
    //�����̈ʒu��soldiersPos�ɂ܂Ƃ߂�
    for (int i = 0; i < 4; i++) {
        soldiersPos_[i] = soldier_[i]->GetPosition();
    }

    //�X�^�[�g�ƃS�[�����擾����
    gameStage_->GetStartPos(startFloor);
    gameStage_->GetGoalPos(goalFloor);

    //���̍��W���擾
    gameStage_->GetFloorPos(floorPos);

    gameStage_->SetSoldiersPos(soldiersPos_);

#pragma endregion
    

   
    
#pragma region ImGui�e�L�X�g
    
#pragma endregion
    
    gameSprite_->Update();
    //�X�e�[�W�X�V
    gameStage_->Update();
    //�e�����̍X�V
    for (int i = 0; i < 4; i++) {
        soldier_[i]->Update(startFloor[i], goalFloor[i], floorPos);
    }
    //�v���C���[�X�V
    //player_->Update();
    //�e�X�̍X�V����
    camera_->Update();
    input_->Update();
    objSphere_->Update();

    //�����蔻��̍X�V
   /* sphere.center = XMVectorSet(objSphere_->GetPosition().x, objSphere_->GetPosition().y, objSphere_->GetPosition().z, 1);
    plane.distance = objPlane_->GetPosition().y;*/
}

void GamePlayScene::Draw()
{
    //�X�v���C�g�̕`��
    spriteCommon_->PreDraw();   //�X�v���C�g�O����
    gameSprite_->Draw();
    //player_->DrawUI();
    spriteCommon_->PostDraw();  //�X�v���C�g�㏈��

    //�I�u�W�F�N�g�̕`��
    Object3d::PreDraw(dxCommon_->GetCommandList()); //�I�u�W�F�N�g�O����

    //�X�e�[�W�`��
    gameStage_->Draw();
    //�v���C���[�`��
    //player_->Draw();
    //�e�����̍X�V
    for (int i = 0; i < 4; i++) {
        soldier_[i]->Draw();
    }

    objSphere_->Draw();

    Object3d::PostDraw();                           //�I�u�W�F�N�g�㏈��

    // �p�[�e�B�N���̕`��
    ParticleManager::PreDraw(dxCommon_->GetCommandList());  //�p�[�e�B�N���O����

    ParticleManager::PostDraw();                            //�p�[�e�B�N���㏈��
}
