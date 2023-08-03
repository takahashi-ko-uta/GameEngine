#include "Input.h"
#include <cassert>
#include <windowsx.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


Input* Input::GetInstance()
{
    static Input instance;
    return &instance;
}

void Input::Initialize(WinApp* winApp)
{
    HRESULT result;
    //�؂�Ă���WinApp�̃C���X�^���X���L�^
    this->winApp = winApp;
    // DirectInput�̏�����
    result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));
    // �L�[�{�[�h�f�o�C�X�̐���
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    assert(SUCCEEDED(result));
    // �}�E�X�f�o�C�X�̐���	
    result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
    assert(SUCCEEDED(result));
    // �L�[�{�[�h�̓��̓f�[�^�`���̃Z�b�g
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
    assert(SUCCEEDED(result));
    // �L�[�{�[�h�̔r�����䃌�x���̃Z�b�g
    result = keyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
    // �}�E�X�̓��̓f�[�^�`���̃Z�b�g
    result = mouse->SetDataFormat(&c_dfDIMouse2); // �W���`��
    assert(SUCCEEDED(result));
    // �}�E�X�̔r�����䃌�x���̃Z�b�g
    result = mouse->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

void Input::Update()
{
    //���j�^�[�̃}�E�X���W�擾
    GetCursorPos(&pt);

    //�O��̃L�[���͂�ۑ�
    memcpy(keyPre, key, sizeof(key));
    // �L�[�{�[�h���̎擾�J�n
    keyboard->Acquire();
    // �S�L�[�̓��͏�Ԃ��擾����
    keyboard->GetDeviceState(sizeof(key), key);

    
    //�O��̃}�E�X���͂�ۑ�
    mouseStatePre = mouseState;
    //�}�E�X�̏��̎擾�J�n
    mouse->Acquire();
    //�S�}�E�X�̓��͏�Ԃ��擾����
    mouse->GetDeviceState(sizeof(mouseState), &mouseState);

}

bool Input::PushKey(BYTE keyNumber)
{
    //�w��L�[�������Ă����true��Ԃ�
    if (key[keyNumber]) {
        return true;
    }
    //�����łȂ����false��Ԃ�
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    if (key[keyNumber] && !keyPre[keyNumber]) {
        return true;
    }
    return false;
}

bool Input::PushMouseLeft()
{
    // 0�ȊO�Ȃ牟���Ă���
    if (mouseState.rgbButtons[0]) {
        return true;
    }

    // �����Ă��Ȃ�
    return false;
}

bool Input::PushMouseRight()
{
    // 0�ȊO�Ȃ牟���Ă���
    if (mouseState.rgbButtons[1]) {
        return true;
    }

    // �����Ă��Ȃ�
    return false;
}

bool Input::PushMouseMiddle()
{
    // 0�ȊO�Ȃ牟���Ă���
    if (mouseState.rgbButtons[2]) {
        return true;
    }

    // �����Ă��Ȃ�
    return false;
}

bool Input::TriggerMouseLeft()
{
    //�O��0�ŁA����0�ȊO�Ȃ牟���Ă���
    if (!mouseStatePre.rgbButtons[0] && mouseState.rgbButtons[0]) {
        return true;
    }

    //�����ĂȂ�
    return false;
}

bool Input::TriggerMouseRight()
{
    //�O��0�ŁA����0�ȊO�Ȃ牟���Ă���
    if (!mouseStatePre.rgbButtons[1] && mouseState.rgbButtons[1]) {
        return true;
    }

    //�����ĂȂ�
    return false;
}

bool Input::TriggerMouseMiddle()
{
    //�O��0�ŁA����0�ȊO�Ȃ牟���Ă���
    if (!mouseStatePre.rgbButtons[2] && mouseState.rgbButtons[2]) {
        return true;
    }

    //�����ĂȂ�
    return false;
}

bool Input::WheelUp()
{
    MouseMove mouseMove = GetMouseMove();
    if (mouseMove.lZ > 0) {
        return true;
    }

    return false;
}

bool Input::WheelDown()
{
    MouseMove mouseMove = GetMouseMove();
    if (mouseMove.lZ < 0) {
        return true;
    }

    return false;
}

bool Input::MouseMoveUp()
{
    MouseMove mouseMove = GetMouseMove();
    if (mouseMove.lY < 0) {
        return true;
    }

    return false;
}

bool Input::MouseMoveDown() 
{
    MouseMove mouseMove = GetMouseMove();
    if (mouseMove.lY > 0) {
        return true;
    }

    return false;
}

bool Input::MouseMoveLeft()
{
    MouseMove mouseMove = GetMouseMove();
    if (mouseMove.lX < 0) {
        return true;
    }

    return false;
}

bool Input::MouseMoveRight()
{
    MouseMove mouseMove = GetMouseMove();
    if (mouseMove.lX > 0) {
        return true;
    }

    return false;
}

Input::XMFLOAT2 Input::GetMouseMonitorPos()
{
    //�}�E�X�̍��W
    POINT Mpt = pt;

    //���j�^�[�̃}�E�X���W�擾
    GetCursorPos(&Mpt);

    //float2�ɕϊ�
    XMFLOAT2 mousePos = { (float)Mpt.x,(float)Mpt.y };
    return mousePos;
}

Input::XMFLOAT2 Input::GetMouseWindowPos()
{
    //�}�E�X�̍��W
    POINT Wpt = pt;

    ScreenToClient(winApp->GetHwnd(), &Wpt);
    
    XMFLOAT2 mousePos = { (float)Wpt.x,(float)Wpt.y};
    return mousePos;
}

Input::MouseMove Input::GetMouseMove()
{
    MouseMove mMove;
    mMove.lX = mouseState.lX;
    mMove.lY = mouseState.lY;
    mMove.lZ = mouseState.lZ;
    return mMove;
}