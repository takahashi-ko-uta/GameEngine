#include "Framework.h"

void Framework::Run()
{
	//ゲームの初期化
	Initialize();

	while (true)//ゲームループ
	{
		//毎フレーム更新
		Update();
		//終了リクエストが来たら抜ける
		if (IsEndRequest())
		{
			break;
		}
		//描画
		Draw();
	}
	//ゲームの終了
	Finalize();
}

void Framework::Initialize()
{
	//WindowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	//DirectXの初期化
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//入力の初期化
	input = new Input();
	input->Initialize(winApp);
}

void Framework::Update()
{
	//inputの更新処理
	input->Update();
}

void Framework::Finalize()
{
	//入力解放
	delete input;
	//DirectX解放
	delete dxCommon;
	//WindowsAPI解放
	winApp->Finalize();
	delete winApp;
}

bool Framework::IsEndRequest()
{
	//Windowsのメッセージ処理
	if (winApp->ProcessMessage()) {
		return true;
	}
	if (input->TriggerKey(DIK_ESCAPE)) {
		return true;
	}

	return false;
}

