#pragma once
#include "Model.h"
#include "Object3d.h"
#include "SoldierRoute.h"

class Normal
{
public:
	//������
	void Initialize(int soldierNum, int normalNum);
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMFLOAT3 pos);
	//�`��
	void Draw();

private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	int normalNum_;
	XMFLOAT3 leaderPos;//�w�肳��Ă��鏰�̍��W
	XMFLOAT3 goalPos;//�ړI�n

};


class Leader
{
public:
	//������
	void Initialize(int soldierNum);
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMFLOAT3 pos);
	//�`��
	void Draw();

	//getter
	XMFLOAT3 GetPosition() { return obj_->GetPosition(); }
private:
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;

	XMFLOAT3 floorPos;//�w�肳��Ă��鏰�̍��W

};


class Solider
{
public:
	//������
	void Initialize(XMFLOAT3 spawnPos, int soldierNum);
	//�I��
	void Finalize();
	//���t���[������
	void Update(XMINT2 startFloor, XMINT2 goalFloor, XMFLOAT3 floorPos[11][11],int selectSoldier, int costMap[11][11]);
	//�`��
	void Draw();

	//getter
	XMFLOAT3 GetSoldierRoutePos() { return soldierRoute_->GetPosition(); }
private:
	SoldierRoute* soldierRoute_ = nullptr;
	Leader* leader = nullptr;
	Normal* normal[8];
};