#pragma once

#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "ImGuiManager.h"
#include "imgui.h"
#include <fstream>
#include <wrl.h>
#include "Framework.h"
#include "GamePlayScene.h"
#include "Camera.h"

class MyGame : public Framework
{
public:
	//������
	void Initialize() override;
	//�I��
	void Finalize() override;
	//���t���[������
	void Update() override;
	//�`��
	void Draw() override;

private:
	ImGuiManager* imGuiManager = nullptr;
	GamePlayScene* scene = nullptr;
};