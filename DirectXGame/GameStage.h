#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Input.h"

class GameStage
{
public://メンバ関数
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	void Select();
	//描画
	void Draw();
private://メンバ変数
	Input* input = nullptr;
	Model* modelGround1_ = nullptr;
	Model* modelGround2_ = nullptr;
	Object3d* objGround_[5][5] = {};

	XMFLOAT2 selectFloor;
	XMFLOAT2 startFloor = { 99.0f,99.0f };	//ありえない数値を入れとく
	XMFLOAT2 goalFloor = { 99.0f,99.0f };	//ありえない数値を入れとく
};

