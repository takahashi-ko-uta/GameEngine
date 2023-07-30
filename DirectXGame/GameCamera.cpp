#include "GameCamera.h"
#include "imgui.h"

void GameCamera::Initialize(Camera* camera)
{
    this->dxCommon_ = DirectXCommon::GetInstance();
    this->input_ = Input::GetInstance();
    this->camera_ = camera;



    //初期位置
    rotObj.m_Angle = 270.0f;
    rotObj.m_Length = 75.0f;
    // 三角関数を使用し、円の位置を割り出す。
    add_x = cos(radius) * rotObj.m_Length;
    add_y = sin(radius) * rotObj.m_Length;

}

void GameCamera::Finalize()
{

}

void GameCamera::Update()
{
#pragma region カメラの移動
    //マウスホイールを押していると
    if (input_->PushMouseMiddle()) {
        //マウスを動かすとカメラを回転
        if (input_->MouseMoveLeft()) {
            rotObj.m_Angle += 1.0f;
            if (rotObj.m_Angle >= 360.0f) { rotObj.m_Angle = 0.0f; }
        }
        if (input_->MouseMoveRight()) { 
            rotObj.m_Angle -= 1.0f;
            if (rotObj.m_Angle <= 0.0f) { rotObj.m_Angle = 360.0f; }
        }
    }

    //マウスホイールで拡大縮小
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

    //回転運動
    //角度をセット
    radius = rotObj.m_Angle * 3.14f / 180.0f;
    //三角関数を使用し、円の位置を割り出す。
    add_x = cos(radius) * rotObj.m_Length;
    add_y = sin(radius) * rotObj.m_Length;
    //結果ででた位置を中心位置に加算し、それを描画位置とする
    rotObj.m_PosX = rotObj.m_CenterX + add_x;
    rotObj.m_PosY = rotObj.m_CenterY + add_y;

    //カメラに反映
    camera_->SetEye({ (float)rotObj.m_PosX, 20.0f, (float)rotObj.m_PosY });
    ImGui::Text("Angle:%f", rotObj.m_Angle);
    ImGui::Text("Length:%f", rotObj.m_Length);
#pragma endregion

    camera_->Update();
}
