#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Model.h"
#include <memory>
#include <list>
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Bullet.h"
#include "WorldTransform.h"

class Player
{
public://メンバ関数
	//初期化
	void Initialize(Camera* camera);
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
	//3D照準
	void Reticle3D();
	//2D照準
	void Reticle2D();
	//描画
	void Draw();
	void DrawUI();
private://メンバ変数
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* spriteCommon_ = nullptr;
	Camera* camera_ = nullptr;

	Sprite* reticle_ = nullptr;

	Object3d* obj_ = nullptr;
	Model* model_ = nullptr;
	WorldTransform PLworldTransform;

	Object3d* obj3Dreticle_ = nullptr;
	Model* model3Dreticle_ = nullptr;
	WorldTransform RTworldTransform;

	Vector3 PLpos;
	std::list<std::unique_ptr<Bullet>> bullets_;
	Vector3 velocity;

	//Vector3 RetclePos;
};

