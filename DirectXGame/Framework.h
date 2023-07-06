#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Input.h"
#include "Audio.h"

class Framework
{
public://�����o�֐�
	//������
	virtual void Initialize();

	//�I��
	virtual void Finalize();

	//���t���[���X�V
	virtual void Update();

	//�`��
	virtual void Draw() = 0;

	//�I���`�F�b�N
	virtual bool IsEndRequest();

	virtual ~Framework() = default;

	//���s
	void Run();

protected:
	//�|�C���^�u����
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
};

