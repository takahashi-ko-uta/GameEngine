#pragma once
#include "Model.h"
#include "Object3d.h"




class Leader
{
public:
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update(XMFLOAT3 pos);
	//描画
	void Draw();

private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

};


class Solider
{
public:
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update(XMFLOAT3 pos);
	//描画
	void Draw();
private:
	Leader* leader = nullptr;
};