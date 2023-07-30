#include "Framework.h"

void Framework::Run()
{
	//�Q�[���̏�����
	Initialize();

	while (true)//�Q�[�����[�v
	{
		//���t���[���X�V
		Update();
		//�I�����N�G�X�g�������甲����
		if (IsEndRequest())
		{
			break;
		}
		//�`��
		Draw();
	}
	//�Q�[���̏I��
	Finalize();
}

void Framework::Initialize()
{
	//WindowsAPI�̏�����
	winApp = WinApp::GetInstance();
	//winApp = new WinApp();
	winApp->Initialize();

	//DirectX�̏�����
	dxCommon = DirectXCommon::GetInstance();
	//dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//���͂̏�����
	input = Input::GetInstance();
	//input = new Input();
	input->Initialize(winApp);

	//�X�v���C�g���ʕ��̏�����
	spriteCommon = SpriteCommon::GetInstance();
	spriteCommon->Initialize(dxCommon);

	//�I�[�f�B�I�̏�����
	audio = Audio::GetInstance();
	audio->Initialize();
}

void Framework::Update()
{
	//input�̍X�V����
	input->Update();
}

void Framework::Finalize()
{
	//�I�[�f�B�I���
	audio->Finalize();

	//WindowsAPI���
	winApp->Finalize();
}

bool Framework::IsEndRequest()
{
	//Windows�̃��b�Z�[�W����
	if (winApp->ProcessMessage()) {
		return true;
	}
	if (input->TriggerKey(DIK_ESCAPE)) {
		return true;
	}

	return false;
}

