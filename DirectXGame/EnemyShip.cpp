#include "EnemyShip.h"
#include "imgui.h"
#include <iostream>     
#include <ctime>        
#include <cstdlib>      

#define PI 3.14159265359

void EnemyShip::Initialize()
{
    this->input_ = Input::GetInstance();
    //���f���ǂݍ���
    model_ = Model::LoadFromOBJ("boat");
    //���̃��f��������
    obj_ = Object3d::Create();
    obj_->SetModel(model_);
    obj_->SetPosition({ 0.0f,3.0f,0.0f });
    obj_->SetScale({ 1.5f,1.5f,1.5f });
    
}

void EnemyShip::Finalize()
{

}

void EnemyShip::Update(XMFLOAT3 floorPos[11][11])
{
    //��������
    std::srand(time(nullptr));

    //�e���̍��W���擾
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            this->floorPos_[y][x] = floorPos[y][x];
        }
    }


    //�D�̃S�[�������߂�
    CreateGoal(floorPos);
    //�����܂ł̓���
    Move();

    obj_->Update();
}

void EnemyShip::CreateGoal(XMFLOAT3 floorPos[11][11])
{
    //�X�|�[���t���O����������A
    if (isSpawn == true) {
        direction = rand() % 4;     //�X�|�[��������������߂�
        floorNum = rand() % 11;     //�������鏰
        randomPos = rand() % 61 - 30;//�X�^�[�g�̍��W
        isSpawn = false;            //�t���O��؂�
        isSelect = true;            //�S�[�������߂�
    }

    switch (direction) {
    case 0://+x����
        obj_->SetRotation({ 0.0f,270.0f,0.0f });        //���f�������ύX
        startPos = { 250.0f,-10.0f,randomPos };         //�X�^�[�g�ʒu
        goalFloor = XMINT2(10, floorNum);               //�������鏰
        goalPos = floorPos_[goalFloor.x][goalFloor.y];  //����������W
        goalPos = { goalPos.x + 13, 0.0f,goalPos.z };   //���̂܂܂��Ə��ɂ߂荞�ނ��ߒ���
        break;

    case 1://-x����
        obj_->SetRotation({ 0.0f,90.0f,0.0f });
        startPos = { -250.0f,-10.0f,randomPos };
        goalFloor = XMINT2(0, floorNum);
        goalPos = floorPos_[goalFloor.x][goalFloor.y];
        goalPos = { goalPos.x -13, 0.0f,goalPos.z };
        break;

    case 2://+z����
        obj_->SetRotation({ 0.0f,180.0f,0.0f });
        startPos = { randomPos,-10.0f,250.0f };
        goalFloor = XMINT2(floorNum, 10);
        goalPos = floorPos_[goalFloor.x][goalFloor.y];
        goalPos = { goalPos.x, 0.0f,goalPos.z + 13 };
        break;

    case 3://-z����
        obj_->SetRotation({ 0.0f,0.0f,0.0f });
        startPos = { randomPos,-10.0f,-250.0f };
        goalFloor = XMINT2(floorNum, 0);
        goalPos = floorPos_[goalFloor.x][goalFloor.y];
        goalPos = { goalPos.x, 0.0f,goalPos.z - 13 };
        break;
    }

    if (isSelect == true) {
        obj_->SetPosition(startPos);
        isSelect = false;
        isMove = true;
    }
}

void EnemyShip::Move()
{
    XMFLOAT3 move = { 0.0f, 0.0f, 0.0f };
    XMFLOAT3 pos = obj_->GetPosition();
    float speed = 0.5f;
  
    //�ŏ��͊C�ɒ���ł��邽�߁A���W���グ��
    if (obj_->GetPosition().y <= goalPos.y) {
        move.y = speed;
    }
    else{
        move.y = 0.0f;
    }

    // �ړ���
    if (goalPos.x < obj_->GetPosition().x) {
        move.x = -speed;
    }
    else if (goalPos.x > obj_->GetPosition().x) {
        move.x = speed;
    }
    else {
        move.x = 0.0f;
    }

    if (goalPos.z < obj_->GetPosition().z) {
        move.z = -speed;
    }
    else if (goalPos.z > obj_->GetPosition().z) {
        move.z = speed;
    }
    else {
        move.z = 0.0f;
    }

    if (isMove == true) {
        //�ړI�n�ɍs���܂ő�����
        if (goalPos.x != obj_->GetPosition().x ||
            goalPos.z != obj_->GetPosition().z) {

            //�ړ�
            pos.x += move.x;
            pos.y += move.y;
            pos.z += move.z;

            num++;

            obj_->SetPosition(pos);
        }
        //�ړI�n�ɒ�������
        else if (goalPos.x == obj_->GetPosition().x &&
            goalPos.z == obj_->GetPosition().z) {
            //�t���O������
            isMove = false;
            isGoal = true;
        };
    }
}

void EnemyShip::Draw()
{
    obj_->Draw();
}
