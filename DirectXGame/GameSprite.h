#pragma once
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Input.h"
#include "Player.h"

class GameSprite
{
public:
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	//�`��
	void Draw();

	void SetCursorPos(DirectX::XMFLOAT2 pos) { mousePos = pos; }
private:
	Player* pl = nullptr;
	Input* input_ = nullptr;
	SpriteCommon* spriteCommon_ = nullptr;
	Sprite* flagSprite_ = nullptr;
	Sprite* mouseCursor_ = nullptr;


	//�}�E�X���W
	DirectX::XMFLOAT2 mousePos;

	bool isMove = false;
	int flagState = 0;
};

