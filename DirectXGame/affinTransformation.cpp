#include "affinTransformation.h"
#include <math.h>
#include "Matrix4.h"

#define PI 3.141592
//
//namespace affinTransformation {
//	void Scale(DirectX::XMFLOAT3 scale) {//スケーリング
//
//
//		//スケーリング行列を宣言
//		Matrix4 matScale;
//		//スケーリング倍率を行列を宣言
//		matScale = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//					0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
//
//		matScale.m[0][0] = scale.x;
//		matScale.m[1][1] = scale.y;
//		matScale.m[2][2] = scale.z;
//
//		Matrix4 matWorld_ = MathMatrix4::Identity();
//		matWorld_ *= matScale;
//	}
//	void Rotate(DirectX::XMFLOAT3 rot) {//回転
//
//		//回転行列を宣言
//		Matrix4 matRot;
//		Matrix4 matRotX, matRotY, matRotZ;
//		//回転倍率を行列を宣言
//		matRot = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//				  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
//		matRotZ = MathMatrix4::Identity();
//		matRotX = MathMatrix4::Identity();
//		matRotY = MathMatrix4::Identity();
//		// Z軸回転の各要素
//		matRotZ.m[0][0] = (float)cos(rot.z);
//		matRotZ.m[0][1] = (float)sin(rot.z);
//		matRotZ.m[1][0] = (float)-sin(rot.z);
//		matRotZ.m[1][1] = (float)cos(rot.z);
//		// X軸回転の各要素
//		matRotX.m[1][1] = (float)cos(rot.x);
//		matRotX.m[1][2] = (float)sin(rot.x);
//		matRotX.m[2][1] = (float)-sin(rot.x);
//		matRotX.m[2][2] = (float)cos(rot.x);
//		// Y軸回転の各要素
//		matRotY.m[0][0] = (float)cos(rot.y);
//		matRotY.m[0][2] = (float)-sin(rot.y);
//		matRotY.m[2][0] = (float)sin(rot.y);
//		matRotY.m[2][2] = (float)cos(rot.y);
//
//		//各軸用回転行列を宣言
//		matRot *= matRotZ *= matRotX *= matRotY;
//
//		worldTransform_.matWorld_ = MathMatrix4::Identity();
//		worldTransform_.matWorld_ *= matRot;
//
//		//行列の転送
//		worldTransform_.TransferMatrix();
//	}
//	void Translate(DirectX::XMFLOAT3 pos) {//移動
//
//		//平行移動行列を宣言
//		Matrix4 matTrans;
//
//		//平行移動を行列を宣言
//		matTrans = MathMatrix4::Identity();
//
//		matTrans.m[3][0] += pos.x;
//		matTrans.m[3][1] += pos.y;
//		matTrans.m[3][2] += pos.z;
//
//		worldTransform_.matWorld_ = MathMatrix4::Identity();
//		worldTransform_.matWorld_ *= matTrans;
//	}
//
//	void Transfer(DirectX::XMFLOAT3 fer) { //上の全て
//
//
//		//スケーリング行列を宣言
//		Matrix4 matScale;
//		//回転行列を宣言
//		Matrix4 matRot;
//		Matrix4 matRotX, matRotY, matRotZ;
//		//平行移動行列を宣言
//		Matrix4 matTrans;
//
//		matScale = MathMatrix4::Identity();
//		matRot = MathMatrix4::Identity();
//		matRotX = MathMatrix4::Identity();
//		matRotY = MathMatrix4::Identity();
//		matRotZ = MathMatrix4::Identity();
//		matTrans = MathMatrix4::Identity();
//
//		//倍率
//		matScale.m[0][0] = worldTransform_.scale_.x;
//		matScale.m[1][1] = worldTransform_.scale_.y;
//		matScale.m[2][2] = worldTransform_.scale_.z;
//		// Z軸回転の各要素
//		matRotZ.m[0][0] = (float)cos(worldTransform_.rotation_.z);
//		matRotZ.m[0][1] = (float)sin(worldTransform_.rotation_.z);
//		matRotZ.m[1][0] = (float)-sin(worldTransform_.rotation_.z);
//		matRotZ.m[1][1] = (float)cos(worldTransform_.rotation_.z);
//		// X軸回転の各要素
//		matRotX.m[1][1] = (float)cos(worldTransform_.rotation_.x);
//		matRotX.m[1][2] = (float)sin(worldTransform_.rotation_.x);
//		matRotX.m[2][1] = (float)-sin(worldTransform_.rotation_.x);
//		matRotX.m[2][2] = (float)cos(worldTransform_.rotation_.x);
//		// Y軸回転の各要素
//		matRotY.m[0][0] = (float)cos(worldTransform_.rotation_.y);
//		matRotY.m[0][2] = (float)-sin(worldTransform_.rotation_.y);
//		matRotY.m[2][0] = (float)sin(worldTransform_.rotation_.y);
//		matRotY.m[2][2] = (float)cos(worldTransform_.rotation_.y);
//		//平行移動
//		matTrans.m[3][0] += worldTransform_.translation_.x;
//		matTrans.m[3][1] += worldTransform_.translation_.y;
//		matTrans.m[3][2] += worldTransform_.translation_.z;
//
//		//各軸用回転行列を宣言
//		matRot *= matRotZ *= matRotX *= matRotY;
//
//		worldTransform_.matWorld_ = MathUtility::Matrix4Identity();
//		worldTransform_.matWorld_ = matScale *= matRot *= matTrans;
//
//	}
//
//	void VecMat(Vector3 vec3, WorldTransform& worldTransform_)
//	{
//		/*vec3.x = (vec3.x * worldTransform_.matWorld_.m[0][0]) +
//				 (vec3.y * worldTransform_.matWorld_.m[1][0]) +
//				 (vec3.z * worldTransform_.matWorld_.m[2][0]) +
//				 (0 * worldTransform_.matWorld_.m[3][0]);
//
//		vec3.y = (vec3.x * worldTransform_.matWorld_.m[0][1]) +
//				 (vec3.y * worldTransform_.matWorld_.m[1][1]) +
//				 (vec3.z * worldTransform_.matWorld_.m[2][1]) +
//				 (0 * worldTransform_.matWorld_.m[3][1]);
//
//		vec3.z = (vec3.x * worldTransform_.matWorld_.m[0][2]) +
//				 (vec3.y * worldTransform_.matWorld_.m[1][2]) +
//				 (vec3.z * worldTransform_.matWorld_.m[2][2]) +
//				 (0 * worldTransform_.matWorld_.m[3][2]);*/
//
//				 //vec3.x = 10;
//
//				 //return vec3;
//	}
//
//}