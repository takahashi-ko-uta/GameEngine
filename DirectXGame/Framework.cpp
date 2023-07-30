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
	winApp = WinApp::GetInstance();
	//winApp = new WinApp();
	winApp->Initialize();

	//DirectXの初期化
	dxCommon = DirectXCommon::GetInstance();
	//dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//入力の初期化
	input = Input::GetInstance();
	//input = new Input();
	input->Initialize(winApp);

	//スプライト共通部の初期化
	spriteCommon = SpriteCommon::GetInstance();
	spriteCommon->Initialize(dxCommon);

	//オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();
}

void Framework::Update()
{
	//inputの更新処理
	input->Update();
}

void Framework::Finalize()
{
	//オーディオ解放
	audio->Finalize();

	//WindowsAPI解放
	winApp->Finalize();
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

