#include "Player.h"
#include "imgui.h"
#include "affinTransformation.h"
#include "Vector3Math.h"

#define PI 3.14159265359

void Player::Initialize(Camera* camera)
{
	input_ = Input::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	camera_ = camera;
	//スプライト
	spriteCommon_ = SpriteCommon::GetInstance();
	//テクスチャのセット
	reticle_ = new Sprite();
	reticle_->Initialize(spriteCommon_, 0, { 0.5f, 0.5f });
	reticle_->SetSize({ 50,50 });

	//オブジェクトの生成
	model_ = Model::LoadFromOBJ("ProtrudingObject");
	obj_ = Object3d::Create();
	obj_->SetModel(model_);
	obj_->SetScale({ 3.0f,3.0f,3.0f });
	PLworldTransform.Initialize();

	model3Dreticle_ = Model::LoadFromOBJ("cube");
	obj3Dreticle_ = Object3d::Create();
	obj3Dreticle_->SetModel(model3Dreticle_);
	obj3Dreticle_->SetScale({ 3.0f,3.0f,3.0f });
	RTworldTransform.Initialize();
}

void Player::Finalize()
{
}

void Player::Update()
{
	//objからworldTransformを取得
	PLworldTransform.matWorld = obj_->GetMat4World();
	RTworldTransform.matWorld = obj3Dreticle_->GetMat4World();

	//Move();
	//Rotate();
	//Attack();
	//Reticle3D();

	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) {
		return bullet->IsDead();
	});

	ImGui::Text("velocity(X:%f, Y:%f, Z:%f)", velocity.x, velocity.y, velocity.z);

	//各毎フレーム処理
	reticle_->Update();
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->Update();
	}
	PLworldTransform.Update();
	obj_->Update();
	RTworldTransform.Update();
	obj3Dreticle_->Update();
}

void Player::Move()
{
	//移動量
	float move = 0.3f;

	XMFLOAT3 pos = obj_->GetPosition();

	//移動
	if (input_->PushKey(DIK_W)) { pos.y += move; }
	if (input_->PushKey(DIK_S)) { pos.y -= move; }
	if (input_->PushKey(DIK_A)) { pos.x -= move; }
	if (input_->PushKey(DIK_D)) { pos.x += move; }

	//反映
	obj_->SetPosition(pos);
}

void Player::Rotate()
{
	XMFLOAT3 rot = obj_->GetRotation();

	//回転
	if (input_->PushKey(DIK_UP)) { rot.x -= 10 * PI / 180; }
	if (input_->PushKey(DIK_DOWN)) { rot.x += 10 * PI / 180; }
	if (input_->PushKey(DIK_LEFT)) { rot.y -= 10 * PI / 180; }
	if (input_->PushKey(DIK_RIGHT)) { rot.y += 10 * PI / 180; }

	//反映
	obj_->SetRotation(rot);
}

void Player::Attack()
{
	if (input_->TriggerMouseLeft()) {
		//弾の速度
		const float speed = 0.05f;
		velocity = { 0.0f,0.0f,speed };
		
		//速度ベクトルを自機の向きに合わせて回転させる
		velocity = Vector3Math::diff(RTworldTransform.GetWorldPosition(), PLworldTransform.GetWorldPosition());
		velocity = Vector3Math::Normalize(velocity) * speed;
		//velocity = Matrix4::Vector3Mat(velocity, PLworldTransform.matWorld);

		//弾の生成と初期化
		std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
		newBullet->Initialize(PLworldTransform.GetWorldPosition(), velocity);
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::Reticle3D()
{
	//自機から3Dレティクルへの距離
	const float kDistancePlayerTo3DReticle = 50.0f;
	//自機から3Dレティクルへのオフセット(z+向き)
	Vector3 offset = { 0, 0, 1.0f };
	//自機のワールド行列の回転を反映
	offset = Matrix4::Vector3Mat(offset, PLworldTransform.matWorld);//
	//ベクトルの長さを整える
	offset = Vector3Math::Normalize(offset) * kDistancePlayerTo3DReticle;
	//3Dレティクルの座標を設定
	Vector3 retcle3DPos = { 0.0f,0.0f,kDistancePlayerTo3DReticle };
	retcle3DPos = Matrix4::Vector3Mat(retcle3DPos, PLworldTransform.matWorld);//
	retcle3DPos.x = retcle3DPos.x + PLworldTransform.GetWorldPosition().x;
	retcle3DPos.y = retcle3DPos.y + PLworldTransform.GetWorldPosition().y;
	retcle3DPos.z = retcle3DPos.z + PLworldTransform.GetWorldPosition().z;

	obj3Dreticle_->SetPosition({ retcle3DPos.x, retcle3DPos.y, retcle3DPos.z });

	//3Dレティクルのワールド座標を取得
	Vector3 retcle2DPos = RTworldTransform.GetWorldPosition();

	//ビュー行列、プロジェクション行列、ビューポート行列を取得
	Matrix4 matView = Vector3Math::ConvertMatrix4(camera_->GetMatView());
	Matrix4 matProjection = Vector3Math::ConvertMatrix4(camera_->GetMatProjection());
	Matrix4 matViewport = Matrix4::CreateViewport(WinApp::window_width, WinApp::window_height,offset);

	//ビュー行列、プロジェクション行列、ビューポート行列を合成
	Matrix4 matVPV = matView * matProjection * matViewport;

	//ワールド→スクリーン座標変換
	retcle2DPos = Matrix4::MatZdivision(retcle2DPos, matVPV);

	//スプライトのレティクルに座標設定
	reticle_->SetPosition({ retcle2DPos.x, retcle2DPos.y });

	ImGui::Text("PlayerPos(X:%f, Y:%f, Z:%f)", obj_->GetPosition().x, obj_->GetPosition().y, obj_->GetPosition().z);
	ImGui::Text("retcle3DPos(X:%f, Y:%f, Z:%f)", retcle3DPos.x, retcle3DPos.y, retcle3DPos.z);
	ImGui::Text("retcle2DPos(X:%f, Y:%f, Z:%f)", retcle2DPos.x, retcle2DPos.y, retcle2DPos.z);
	ImGui::Text("RT2DPos-RT3Dpos(X:%f, Y:%f)", retcle2DPos.x - WinApp::window_width/2, retcle2DPos.y - WinApp::window_height/2);
}

void Player::Reticle2D()
{
	//ウィンドウのマウス座標を取得
	XMFLOAT2 mousePos = input_->GetMouseWindowPos();

	//ビュー行列、プロジェクション行列、ビューポート行列の合計行列を計算する
	Matrix4 matVPV;
	//合成行列の逆行列を計算する
	Matrix4 matInverseVPV;
}

void Player::Draw()
{
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->Draw();
	}
	obj3Dreticle_->Draw();
	obj_->Draw();
}

void Player::DrawUI()
{
	reticle_->Draw();
}
