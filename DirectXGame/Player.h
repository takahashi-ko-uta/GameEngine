#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Model.h"

class Player
{
public://メンバ関数
	//初期化
	void Initialize(Input* input);
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	//移動
	void Move();
	//回転
	void Rotate();
	//描画
	void Draw();

private://メンバ変数
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;
};

