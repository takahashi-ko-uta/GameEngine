#include "GameStage.h"
#include "imgui.h"

void GameStage::Initialize()
{
    input = Input::GetInstance();

	//���f���ǂݍ���
	modelGround1_ = Model::LoadFromOBJ("ground");
	modelGround2_ = Model::LoadFromOBJ("ground2");

#pragma region ���I�u�W�F�N�g������
    //�n�ʂ̃I�u�W�F�N�g������
    for (int i = 0; i < stageSize; i++) {
        for (int j = 0; j < stageSize; j++) {
            //�I�u�W�F�N�g����
            objGround_[i][j] = Object3d::Create();
            //3D�I�u�W�F�N�g��3D���f�����Ђ��t��
            if ((i + j) % 2 == 0) {
                objGround_[i][j]->SetModel(modelGround1_);
            }
            else {
                objGround_[i][j]->SetModel(modelGround2_);
            }
            //3D�I�u�W�F�N�g�̃X�P�[�����w��
            float size = 5.0f;
            objGround_[i][j]->SetScale({ size,size,size });

            //3D�I�u�W�F�N�g�̈ʒu���w��
            objGround_[i][j]->SetPosition({ ((float)i - stageSize / 2) * size * 2, 0.0f, ((float)j - stageSize / 2) * size * 2 });
        }
    }
#pragma endregion 
    
    for (int i = 0; i < 4; i++){
        startFloor[i] = { 99,99 };
        goalFloor[i] = { 99,99 };
    }


    //�����̃X�|�[���ʒu��ݒ�
    spawnFloor[0] = { 4,4 };
    spawnFloor[1] = { 4,6 };
    spawnFloor[2] = { 6,4 };
    spawnFloor[3] = { 6,6 };
}

void GameStage::Finalize()
{
}

void GameStage::Update()
{
    Select();

    //�e�n�ʃI�u�W�F�N�g�̍X�V
    for (int i = 0; i < stageSize; i++) {
        for (int j = 0; j < stageSize; j++) {
            objGround_[i][j]->Update();
        }
    }
}

void GameStage::Select()
{
    //�����̂��鏰���擾
    SetSoldiersFloor();

#pragma region ���̑I��
    if (input->TriggerKey(DIK_W)) {
        selectFloor.y += 1;
        if (selectFloor.y == stageSize) { selectFloor.y = 0; }
    }
    if (input->TriggerKey(DIK_S)) {
        selectFloor.y -= 1;
        if (selectFloor.y == -1) { selectFloor.y = stageSize - 1; }
    }
    if (input->TriggerKey(DIK_A)) {
        selectFloor.x -= 1;
        if (selectFloor.x == -1) { selectFloor.x = stageSize - 1; }
    }
    if (input->TriggerKey(DIK_D)) {
        selectFloor.x += 1;
        if (selectFloor.x == stageSize) { selectFloor.x = 0; }
    }
#pragma endregion

    //���̏󋵂ɉ����ĐF��ς���   
    ChangeFloorColor();
    
    //�X�y�[�X����������X�^�[�g�n�_��ݒ�
    if (input->TriggerKey(DIK_SPACE)) {
        for (int i = 0; i < 4; i++) {
            //�X�^�[�g�͏�ɍX�V
            startFloor[i] = soldiersFloor[i];
            //�I���������̏�ɕ�����������A���̕����̔ԍ����擾
            if (selectFloor.x == soldiersFloor[i].x && selectFloor.y == soldiersFloor[i].y) {
                selectSoldier = i;
            }
            //�ԍ����擾���������̃S�[�����X�V
            else if (selectSoldier != 5) {
                goalFloor[selectSoldier] = selectFloor;
            }
        }
    }

    //�X�^�[�g�n�_�A�S�[���n�_�����Z�b�g
    if (input->TriggerKey(DIK_R)) {
        for (int i = 0; i < 4; i++){
            startFloor[i] = {99,99};
            goalFloor[i] = {99,99};
        }
    }

    /*ImGui::Text("soldiers0(X:%.0f, Y:%.0f)", soldiersFloor[0].x, soldiersFloor[0].y);
    ImGui::Text("soldiers1(X:%.0f, Y:%.0f)", soldiersFloor[1].x, soldiersFloor[1].y);
    ImGui::Text("soldiers2(X:%.0f, Y:%.0f)", soldiersFloor[2].x, soldiersFloor[2].y);
    ImGui::Text("soldiers3(X:%.0f, Y:%.0f)", soldiersFloor[3].x, soldiersFloor[3].y);*/


    ImGui::Text("select(X:%.0f, Y:%.0f)", selectFloor.x, selectFloor.y);

    ImGui::Text("selectSoldier: %d", selectSoldier);

    ImGui::Text("S[0](%.0f,%.0f),[1](%.0f,%.0f),[2](%.0f,%.0f),[3](%.0f,%.0f)",
        soldiersFloor[0].x, soldiersFloor[0].y, soldiersFloor[1].x, soldiersFloor[1].y, soldiersFloor[2].x, soldiersFloor[2].y, soldiersFloor[3].x, soldiersFloor[3].y);

    ImGui::Text("S[0](%.0f,%.0f),[1](%.0f,%.0f),[2](%.0f,%.0f),[3](%.0f,%.0f)",
        startFloor[0].x, startFloor[0].y, startFloor[1].x, startFloor[1].y, startFloor[2].x, startFloor[2].y, startFloor[3].x, startFloor[3].y);
    ImGui::Text("G[0](%.0f,%.0f),[1](%.0f,%.0f),[2](%.0f,%.0f),[3](%.0f,%.0f)",
        goalFloor[0].x, goalFloor[0].y, goalFloor[1].x, goalFloor[1].y, goalFloor[2].x, goalFloor[2].y, goalFloor[3].x, goalFloor[3].y);
}

void GameStage::SetSoldiersFloor()
{
    for (int i = 0; i < stageSize; i++) {
        for (int j = 0; j < stageSize; j++) {
            for (int x = 0; x < 4; x++) {
                //������x,z�Ɗe����x,z���ׂē�����������ۑ�����
                if (objGround_[i][j]->GetPosition().x == soldiersPos[x].x &&
                    objGround_[i][j]->GetPosition().z == soldiersPos[x].z) {

                    soldiersFloor[x] = { i,j };
                }
            }
        }
    }
}

void GameStage::ChangeFloorColor()
{
    for (int i = 0; i < stageSize; i++) {
        for (int j = 0; j < stageSize; j++) {
            //�I�����ꂽ�I�u�W�F�N�g(��)��Ԃɂ���
            if (i == selectFloor.x && j == selectFloor.y) {
                objGround_[i][j]->SetColor({ 0.5,0,0,1 });
            }
            //�X�^�[�g�n�_�̃I�u�W�F�N�g(��)��΂ɂ���
            else if (i == startFloor[selectSoldier].x && j == startFloor[selectSoldier].y) {
                objGround_[i][j]->SetColor({ 0,0.5,0,1 });
            }
            //�S�[���n�_�̃I�u�W�F�N�g(��)��ɂ���
            else if (i == goalFloor[selectSoldier].x && j == goalFloor[selectSoldier].y) {
                objGround_[i][j]->SetColor({ 0,0,0.5,1 });
            }
            //�����w�肳��ĂȂ��I�u�W�F�N�g(��)�͌��̐F
            else {
                objGround_[i][j]->SetColor({ 1,1,1,1 });
            }
        }
    }


    //objGround_[selectFloor.x][selectFloor.y]->SetColor({ 0.5,0,0,1 });
    //for (int i = 0; i < 4; i++) {
    //    objGround_[startFloor[i].x][startFloor[i].y]->SetColor({0,0.5,0,1});
    //    objGround_[goalFloor[i].x][goalFloor[i].y]->SetColor({ 0,0,0.5,1 });
    //}
}

void GameStage::Draw()
{
    //�X�e�[�W�̕`��
    for (int i = 0; i < stageSize; i++) {
        for (int j = 0; j < stageSize; j++) {
            objGround_[i][j]->Draw();
        }
    }
}

const XMFLOAT3 GameStage::GetSpawnFloor(int num)
{

    XMFLOAT3 spawnPos;

    int x = spawnFloor[num].x;
    int y = spawnFloor[num].y;

    spawnPos = objGround_[x][y]->GetPosition();
    
    return spawnPos;
}

void GameStage::SetSoldiersPos(XMFLOAT3 soldiersPos[4])
{
    for (int i = 0; i < 4; i++) {
        this->soldiersPos[i] = soldiersPos[i];
    }
}