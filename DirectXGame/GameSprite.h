#pragma once
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Input.h"
#include "Player.h"

class GameSprite
{
public:
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	//描画
	void Draw();

	void SetCursorPos(DirectX::XMFLOAT2 pos) { mousePos = pos; }
private:
	Player* pl = nullptr;
	Input* input_ = nullptr;
	SpriteCommon* spriteCommon_ = nullptr;
	Sprite* flagSprite_ = nullptr;
	Sprite* mouseCursor_ = nullptr;


	//マウス座標
	DirectX::XMFLOAT2 mousePos;

	bool isMove = false;
	int flagState = 0;
};

