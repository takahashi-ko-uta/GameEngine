#pragma once
#include "Model.h"
#include "Object3d.h"

class EnemyShip
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
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	int32_t direction = 0;

};

