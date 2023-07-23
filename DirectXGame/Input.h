#pragma once
#include <Windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION		0x0800	//DirectInput�̃o�[�W�����w��
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
	//namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
public: //�����o�֐�
	static Input* GetInstance();
	//������
	void Initialize(WinApp* winApp);
	//�X�V
	void Update();
	/// <summary>
	/// �L�[�̉����������`�F�b�N
	/// </summary>
	/// <param name = "keyNumber">�L�[�ԍ�(DIK_0��)</param>
	/// <returns>������Ă��邩</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// �L�[�̃g���K�[���`�F�b�N
	/// </summary>
	/// <param name = "keyNumber">�L�[�ԍ�(DIK_0��)</param>
	/// <returns>�g���K�[��</returns>
	bool TriggerKey(BYTE keyNumber);

	/// <summary>
	/// �}�E�X�̍��{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool PushMouseLeft();

	/// <summary>
	/// �}�E�X�̉E�{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool PushMouseRight();

	/// <summary>
	/// �}�E�X�̒��{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool PushMouseMiddle();

	/// <summary>
	/// �}�E�X�̍��{�^���g���K�[���`�F�b�N
	/// </summary>
	/// <returns>�g���K�[��</returns>
	bool TriggerMouseLeft();

	/// <summary>
	/// �}�E�X�̉E�{�^���g���K�[���`�F�b�N
	/// </summary>
	/// <returns>�g���K�[��</returns>
	bool TriggerMouseRight();

	/// <summary>
	/// �}�E�X�̒��{�^���g���K�[���`�F�b�N
	/// </summary>
	/// <returns>�g���K�[��</returns>
	bool TriggerMouseMiddle();

	/// <summary>
	/// �}�E�X�̃z�C�[������ɂ��������`�F�b�N
	/// </summary>
	bool WheelUp();

	/// <summary>
	/// �}�E�X�̃z�C�[�������ɂ��������`�F�b�N
	/// </summary>
	bool WheelDown();

	/// <summary>
	/// �}�E�X���ɓ��������`�F�b�N
	/// </summary>
	bool MouseMoveUp();

	/// <summary>
	/// �}�E�X���ɓ��������`�F�b�N
	/// </summary>
	bool MouseMoveDown();

	/// <summary>
	/// �}�E�X���ɓ��������`�F�b�N
	/// </summary>
	bool MouseMoveLeft();

	/// <summary>
	/// �}�E�X���ɓ��������`�F�b�N
	/// </summary>
	bool MouseMoveRight();

	/// <summary>
	/// ���j�^�[�̍�����Βl(0,0)�ɂ����Ƃ��̃}�E�X���W
	/// </summary>
	/// <returns>�}�E�X���W</returns>
	POINT GatMouseMonitorPos() { return pt; }

	/// <summary>
	/// �E�B���h�E��̃}�E�X���W
	/// </summary>
	XMFLOAT2 GetMouseWindowPos();

	/// <summary>
	/// �}�E�X�ړ��ʂ��擾
	/// </summary>
	/// <returns>�}�E�X�ړ���</returns>
	MouseMove GetMouseMove();

private://�����o�ϐ�
	//�L�[�{�[�h�f�o�C�X
	ComPtr<IDirectInputDevice8> keyboard;
	//�S�L�[�̏��
	BYTE key[256] = {};
	//�O��̑S�L�[�̏��
	BYTE keyPre[256] = {};
	//�L�[�{�[�h�f�o�C�X
	ComPtr<IDirectInputDevice8> mouse;
	//�}�E�X�̏��
	DIMOUSESTATE2 mouseState = {};
	//�O��̃}�E�X�̏��
	DIMOUSESTATE2 mouseStatePre = {};
	//DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> directInput;
	//WindoeAPI
	WinApp* winApp = nullptr;
	//�}�E�X�̍��W
	POINT pt;
};

