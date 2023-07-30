#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Model.h"
#include <memory>
#include <list>

#include "Bullet.h"
#include "WorldTransform.h"

class Player
{
public://メンバ関数
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	//移動
	void Move();
	//回転
	void Rotate();
	//クリック
	void Attack();
	//描画
	void Draw();

private://メンバ変数
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Object3d* obj_ = nullptr;
	
	Vector3 PLpos;
	std::list<std::unique_ptr<Bullet>> bullets_;
	WorldTransform w;
	Vector3 velocity;
};

