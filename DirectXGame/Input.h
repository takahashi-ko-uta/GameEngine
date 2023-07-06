#pragma once
#include <Windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION		0x0800	//DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include "WinApp.h"

class Input
{
public:
	//namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

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

private://�����o�ϐ�
	//�L�[�{�[�h�f�o�C�X
	ComPtr<IDirectInputDevice8> keyboard;
	//�S�L�[�̏��
	BYTE key[256] = {};
	//�O��̑S�L�[�̏��
	BYTE keyPre[256] = {};
	//DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> directInput;
	//WindoeAPI
	WinApp* winApp = nullptr;
};

