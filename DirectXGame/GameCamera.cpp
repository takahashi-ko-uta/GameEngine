#include "GameCamera.h"

void GameCamera::Initialize(DirectXCommon* dxCommon, Input* input, Camera* camera)
{
    this->dxCommon_ = dxCommon;
    this->input_ = input;
    this->camera_ = camera;

    // �O�p�֐����g�p���A�~�̈ʒu������o���B
    add_x = cos(radius) * rotObj.m_Length;
    add_y = sin(radius) * rotObj.m_Length;
}

void GameCamera::Finalize()
{

}

void GameCamera::Update()
{
#pragma region �J�����̈ړ�
    //�}�E�X�z�C�[���������Ă����
    if (input_->PushMouseMiddle()) {
        //�}�E�X�𓮂����ƃJ��������]
        if (input_->MouesMoveLeft()) { rotObj.m_Angle += 1.0f; }
        if (input_->MouesMoveRight()) { rotObj.m_Angle -= 1.0f; }
    }

    //�}�E�X�z�C�[���Ŋg��k��
    if (input_->WheelUp()) {
        if (rotObj.m_Length >= 25.0f) {
            rotObj.m_Length -= 3.0f;
        }
    }
    if (input_->WheelDown()) {
        if (rotObj.m_Length <= 75.0f) {
            rotObj.m_Length += 3.0f;
        }
    }

    //��]�^��
    //�p�x���Z�b�g
    radius = rotObj.m_Angle * 3.14f / 180.0f;
    //�O�p�֐����g�p���A�~�̈ʒu������o���B
    add_x = cos(radius) * rotObj.m_Length;
    add_y = sin(radius) * rotObj.m_Length;
    //���ʂłł��ʒu�𒆐S�ʒu�ɉ��Z���A�����`��ʒu�Ƃ���
    rotObj.m_PosX = rotObj.m_CenterX + add_x;
    rotObj.m_PosY = rotObj.m_CenterY + add_y;

    //�J�����ɔ��f
    camera_->SetEye({ (float)rotObj.m_PosX, 20.0f, (float)rotObj.m_PosY });

#pragma endregion

    camera_->Update();
}