#include "MyGame.h"


void MyGame::Initialize()
{
    //��ՃV�X�e���̏�����
    Framework::Initialize();

    //�ŏ��̃V�[����������
    //imGuiManager������
    imGuiManager = new ImGuiManager();
    imGuiManager->Initialize(winApp, dxCommon);

    //�V�[���̏�����
    scene = new GamePlayScene();
    scene->Initialize();
}

void MyGame::Finalize()
{
    //�ŏ��̃V�[���̏I��
    imGuiManager->Finalize();
    delete imGuiManager;

    //�V�[���̏I������
    scene->Finalize();
  
    //��ՃV�X�e���̏I��
    Framework::Finalize();
}

void MyGame::Update()
{
    //��ՃV�X�e���̍X�V
    Framework::Update();

    //�ŏ��̃V�[���̍X�V
  
    imGuiManager->Begin();
    //�V�[���̖��t���[������
    scene->Update();

    //ImGui�̃f���E�B���h�E�\��
    //ImGui::ShowDemoWindow();
    imGuiManager->End();
}

void MyGame::Draw()
{
    //�`��O����
    dxCommon->PreDraw();

    //�V�[���̕`��
    scene->Draw();

    imGuiManager->Draw();

    //�`��㏈��
    dxCommon->PostDraw();
}