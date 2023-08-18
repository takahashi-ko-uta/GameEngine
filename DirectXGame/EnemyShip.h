#pragma once
#include "Model.h"
#include "Object3d.h"

class EnemyShip
{
public:
	//‰Šú‰»
	void Initialize();
	//I—¹
	void Finalize();
	//–ˆƒtƒŒ[ƒ€ˆ—
	void Update();
	//•`‰æ
	void Draw();
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;
};

