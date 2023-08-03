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
    //借りてきたWinAppのインスタンスを記録
    this->winApp = winApp;
    // DirectInputの初期化
    result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));
    // キーボードデバイスの生成
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    assert(SUCCEEDED(result));
    // マウスデバイスの生成	
    result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
    assert(SUCCEEDED(result));
    // キーボードの入力データ形式のセット
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
    assert(SUCCEEDED(result));
    // キーボードの排他制御レベルのセット
    result = keyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
    // マウスの入力データ形式のセット
    result = mouse->SetDataFormat(&c_dfDIMouse2); // 標準形式
    assert(SUCCEEDED(result));
    // マウスの排他制御レベルのセット
    result = mouse->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

void Input::Update()
{
    //モニターのマウス座標取得
    GetCursorPos(&pt);

    //前回のキー入力を保存
    memcpy(keyPre, key, sizeof(key));
    // キーボード情報の取得開始
    keyboard->Acquire();
    // 全キーの入力状態を取得する
    keyboard->GetDeviceState(sizeof(key), key);

    
    //前回のマウス入力を保存
    mouseStatePre = mouseState;
    //マウスの情報の取得開始
    mouse->Acquire();
    //全マウスの入力状態を取得する
    mouse->GetDeviceState(sizeof(mouseState), &mouseState);

}

bool Input::PushKey(BYTE keyNumber)
{
    //指定キーを押していればtrueを返す
    if (key[keyNumber]) {
        return true;
    }
    //そうでなければfalseを返す
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
    // 0以外なら押している
    if (mouseState.rgbButtons[0]) {
        return true;
    }

    // 押していない
    return false;
}

bool Input::PushMouseRight()
{
    // 0以外なら押している
    if (mouseState.rgbButtons[1]) {
        return true;
    }

    // 押していない
    return false;
}

bool Input::PushMouseMiddle()
{
    // 0以外なら押している
    if (mouseState.rgbButtons[2]) {
        return true;
    }

    // 押していない
    return false;
}

bool Input::TriggerMouseLeft()
{
    //前回が0で、今回が0以外なら押している
    if (!mouseStatePre.rgbButtons[0] && mouseState.rgbButtons[0]) {
        return true;
    }

    //押してない
    return false;
}

bool Input::TriggerMouseRight()
{
    //前回が0で、今回が0以外なら押している
    if (!mouseStatePre.rgbButtons[1] && mouseState.rgbButtons[1]) {
        return true;
    }

    //押してない
    return false;
}

bool Input::TriggerMouseMiddle()
{
    //前回が0で、今回が0以外なら押している
    if (!mouseStatePre.rgbButtons[2] && mouseState.rgbButtons[2]) {
        return true;
    }

    //押してない
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
    //マウスの座標
    POINT Mpt = pt;

    //モニターのマウス座標取得
    GetCursorPos(&Mpt);

    //float2に変換
    XMFLOAT2 mousePos = { (float)Mpt.x,(float)Mpt.y };
    return mousePos;
}

Input::XMFLOAT2 Input::GetMouseWindowPos()
{
    //マウスの座標
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