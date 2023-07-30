#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Model.h"

class Bullet
{
public://メンバ関数
	//初期化
	void Initialize(Vector3 pos, const Vector3& velocity);
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	//描画
	void Draw();

	//getter
	bool IsDead() const { return isDead; }

private://メンバ変数
	Input* input_ = nullptr;
	Vector3 pos_;
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	Vector3 velocity_;
	//消えるまでの時間
	static const int32_t lifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer = lifeTime;
	//デスフラグ
	bool isDead = false;
};

