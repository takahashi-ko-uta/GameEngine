#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Input.h"
#include "SearchRoute.h"

class Soldier
{
public:
	//初期化
	void Initialize(XMFLOAT3 spawnPos, int soldierNum);
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	//描画
	void Draw();

	//getter
	const XMFLOAT3 GetPosition() const { return obj_->GetPosition(); }

private:
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	XMFLOAT3 spawnPos_;//初期位置
};

