#include "GameStage.h"

void GameStage::Initialize()
{
	//モデル読み込み
	modelGround1_ = Model::LoadFromOBJ("ground");
	modelGround2_ = Model::LoadFromOBJ("ground2");

    //地面のオブジェクト初期化
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            //オブジェクト生成
            objGround_[i][j] = Object3d::Create();
            //3Dオブジェクトと3Dモデルをひも付け
            if ((i + j) % 2 == 0) {
                objGround_[i][j]->SetModel(modelGround1_);
            }
            else {
                objGround_[i][j]->SetModel(modelGround2_);
            }
            //3Dオブジェクトのスケールを指定
            float size = 5.0f;
            objGround_[i][j]->SetScale({ size,size,size });

            //3Dオブジェクトの位置を指定
            objGround_[i][j]->SetPosition({ ((float)i - 2) * size * 2, -2.5f, ((float)j - 2) * size * 2 });
        }
    }
}

void GameStage::Finalize()
{
}

void GameStage::Update()
{

    //各地面オブジェクトの更新
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            objGround_[i][j]->Update();
        }
    }
}

void GameStage::Draw()
{
    //ステージの描画
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            objGround_[i][j]->Draw();
        }
    }
}
