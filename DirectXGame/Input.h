#pragma once
#include <Windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION		0x0800	//DirectInputのバージョン指定
#include <dinput.h>
#include "WinApp.h"
#include <DirectXMath.h>

class Input
{
public:
	struct MouseMove {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};	
private:
	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
public: //メンバ関数
	static Input* GetInstance();
	//初期化
	void Initialize(WinApp* winApp);
	//更新
	void Update();
	/// <summary>
	/// キーの押したかをチェック
	/// </summary>
	/// <param name = "keyNumber">キー番号(DIK_0等)</param>
	/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// <param name = "keyNumber">キー番号(DIK_0等)</param>
	/// <returns>トリガーか</returns>
	bool TriggerKey(BYTE keyNumber);

	/// <summary>
	/// マウスの左ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool PushMouseLeft();

	/// <summary>
	/// マウスの右ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool PushMouseRight();

	/// <summary>
	/// マウスの中ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool PushMouseMiddle();

	/// <summary>
	/// マウスの左ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool TriggerMouseLeft();

	/// <summary>
	/// マウスの右ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool TriggerMouseRight();

	/// <summary>
	/// マウスの中ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool TriggerMouseMiddle();

	/// <summary>
	/// マウスのホイールが上にいったかチェック
	/// </summary>
	bool WheelUp();

	/// <summary>
	/// マウスのホイールが下にいったかチェック
	/// </summary>
	bool WheelDown();

	/// <summary>
	/// マウスがに動いたかチェック
	/// </summary>
	bool MouseMoveUp();

	/// <summary>
	/// マウスがに動いたかチェック
	/// </summary>
	bool MouseMoveDown();

	/// <summary>
	/// マウスがに動いたかチェック
	/// </summary>
	bool MouseMoveLeft();

	/// <summary>
	/// マウスがに動いたかチェック
	/// </summary>
	bool MouseMoveRight();

	/// <summary>
	/// モニターの左上を絶対値(0,0)にしたときのマウス座標
	/// </summary>
	/// <returns>マウス座標</returns>
	POINT GatMouseMonitorPos() { return pt; }

	/// <summary>
	/// ウィンドウ上のマウス座標
	/// </summary>
	XMFLOAT2 GetMouseWindowPos();

	/// <summary>
	/// マウス移動量を取得
	/// </summary>
	/// <returns>マウス移動量</returns>
	MouseMove GetMouseMove();

private://メンバ変数
	//キーボードデバイス
	ComPtr<IDirectInputDevice8> keyboard;
	//全キーの状態
	BYTE key[256] = {};
	//前回の全キーの状態
	BYTE keyPre[256] = {};
	//キーボードデバイス
	ComPtr<IDirectInputDevice8> mouse;
	//マウスの状態
	DIMOUSESTATE2 mouseState = {};
	//前回のマウスの状態
	DIMOUSESTATE2 mouseStatePre = {};
	//DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput;
	//WindoeAPI
	WinApp* winApp = nullptr;
	//マウスの座標
	POINT pt;
};

