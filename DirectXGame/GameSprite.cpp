#include "GameSprite.h"

void GameSprite::Initialize()
{
    input_ = Input::GetInstance();
    spriteCommon_ = SpriteCommon::GetInstance();
    //�e�N�X�`���̃Z�b�g
    spriteCommon_->LoadTexture(0, "2Dreticle.png");
    spriteCommon_->LoadTexture(1, "flag.png");

    mouseCursor_ = new Sprite();
    mouseCursor_->Initialize(spriteCommon_, 0, { 0.5f, 0.5f });
    mouseCursor_->SetSize({ 50,50 });

    flagSprite_ = new Sprite();
    flagSprite_->Initialize(spriteCommon_, 1, { 0.5f,0.5f });
    flagSprite_->SetSize({ 100,50 });
    flagSprite_->SetPosition({ 50.0f, 600.0f });
    
}

void GameSprite::Finalize()
{

}

void GameSprite::Update()
{
    //�E�B���h�E�̃}�E�X���W���擾
    mousePos = input_->GetMouseWindowPos();
    //���e�B�N���̃e�N�X�`���Ƀ}�E�X���W�𔽉f
    mouseCursor_->SetPosition(mousePos);

    mouseCursor_->Update();
    flagSprite_->Update();
}

void GameSprite::Draw()
{
    flagSprite_->Draw();
    mouseCursor_->Draw();
}
