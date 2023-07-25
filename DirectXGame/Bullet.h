#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Model.h"

class Bullet
{
public://メンバ関数
	//初期化
	void Initialize(Input* input, XMFLOAT3 pos);
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	//描画
	void Draw();

private://メンバ変数
	Input* input_ = nullptr;
	XMFLOAT3 pos_;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;
};

