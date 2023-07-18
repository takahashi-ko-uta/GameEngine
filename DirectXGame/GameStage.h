#pragma once
#include "Model.h"
#include "Object3d.h"

class GameStage
{
public://メンバ関数
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	//描画
	void Draw();
private://メンバ変数
	Model* modelGround1_ = nullptr;
	Model* modelGround2_ = nullptr;
	Object3d* objGround_[5][5] = {};
};

