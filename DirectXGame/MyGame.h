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
	//‰Šú‰»
	void Initialize() override;
	//I—¹
	void Finalize() override;
	//–ˆƒtƒŒ[ƒ€ˆ—
	void Update() override;
	//•`‰æ
	void Draw() override;

private:
	ImGuiManager* imGuiManager = nullptr;
	GamePlayScene* scene = nullptr;
};