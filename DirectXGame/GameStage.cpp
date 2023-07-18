#include "GameStage.h"

void GameStage::Initialize()
{
	//���f���ǂݍ���
	modelGround1_ = Model::LoadFromOBJ("ground");
	modelGround2_ = Model::LoadFromOBJ("ground2");

    //�n�ʂ̃I�u�W�F�N�g������
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            //�I�u�W�F�N�g����
            objGround_[i][j] = Object3d::Create();
            //3D�I�u�W�F�N�g��3D���f�����Ђ��t��
            if ((i + j) % 2 == 0) {
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
}

void GameStage::Finalize()
{
}

void GameStage::Update()
{

    //�e�n�ʃI�u�W�F�N�g�̍X�V
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            objGround_[i][j]->Update();
        }
    }
}

void GameStage::Draw()
{
    //�X�e�[�W�̕`��
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            objGround_[i][j]->Draw();
        }
    }
}
