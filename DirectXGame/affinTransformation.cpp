#include "affinTransformation.h"
#include <math.h>
#include "Matrix4.h"

#define PI 3.141592

namespace affinTransformation {
	void Scale(WorldTransform& worldTransform_) {//スケーリング


		//スケーリング行列を宣言
		Matrix4 matScale;
		//スケーリング倍率を行列を宣言
		matScale = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		matScale.m[0][0] = worldTransform_.scale.x;
		matScale.m[1][1] = worldTransform_.scale.y;
		matScale.m[2][2] = worldTransform_.scale.z;

		worldTransform_.matWorld = Matrix4::Identity();
		worldTransform_.matWorld *= matScale;


	}
	void Rotate(WorldTransform& worldTransform_) {//回転

		//回転行列を宣言
		Matrix4 matRot;
		Matrix4 matRotX, matRotY, matRotZ;
		//回転倍率を行列を宣言
		matRot = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		matRotZ = Matrix4::Identity();
		matRotX = Matrix4::Identity();
		matRotY = Matrix4::Identity();
		// Z軸回転の各要素
		matRotZ.m[0][0] = (float)cos(worldTransform_.rotation.z);
		matRotZ.m[0][1] = (float)sin(worldTransform_.rotation.z);
		matRotZ.m[1][0] = (float)-sin(worldTransform_.rotation.z);
		matRotZ.m[1][1] = (float)cos(worldTransform_.rotation.z);
		// X軸回転の各要素
		matRotX.m[1][1] = (float)cos(worldTransform_.rotation.x);
		matRotX.m[1][2] = (float)sin(worldTransform_.rotation.x);
		matRotX.m[2][1] = (float)-sin(worldTransform_.rotation.x);
		matRotX.m[2][2] = (float)cos(worldTransform_.rotation.x);
		// Y軸回転の各要素
		matRotY.m[0][0] = (float)cos(worldTransform_.rotation.y);
		matRotY.m[0][2] = (float)-sin(worldTransform_.rotation.y);
		matRotY.m[2][0] = (float)sin(worldTransform_.rotation.y);
		matRotY.m[2][2] = (float)cos(worldTransform_.rotation.y);

		//各軸用回転行列を宣言
		matRot *= matRotZ *= matRotX *= matRotY;

		worldTransform_.matWorld = Matrix4::Identity();
		worldTransform_.matWorld *= matRot;

		//行列の転送
		//worldTransform_.TransferMatrix();
	}
	void Translate(WorldTransform& worldTransform_) {//移動

		//平行移動行列を宣言
		Matrix4 matTrans;

		//平行移動を行列を宣言
		matTrans = Matrix4::Identity();

		matTrans.m[3][0] += worldTransform_.translation.x;
		matTrans.m[3][1] += worldTransform_.translation.y;
		matTrans.m[3][2] += worldTransform_.translation.z;

		worldTransform_.matWorld = Matrix4::Identity();
		worldTransform_.matWorld *= matTrans;
	}

	void Transfer(WorldTransform& worldTransform_) { //上の全て


		//スケーリング行列を宣言
		Matrix4 matScale;
		//回転行列を宣言
		Matrix4 matRot;
		Matrix4 matRotX, matRotY, matRotZ;
		//平行移動行列を宣言
		Matrix4 matTrans;

		matScale = Matrix4::Identity();
		matRot = Matrix4::Identity();
		matRotX = Matrix4::Identity();
		matRotY = Matrix4::Identity();
		matRotZ = Matrix4::Identity();
		matTrans = Matrix4::Identity();

		//倍率
		matScale.m[0][0] = worldTransform_.scale.x;
		matScale.m[1][1] = worldTransform_.scale.y;
		matScale.m[2][2] = worldTransform_.scale.z;
		// Z軸回転の各要素
		matRotZ.m[0][0] = (float)cos(worldTransform_.rotation.z);
		matRotZ.m[0][1] = (float)sin(worldTransform_.rotation.z);
		matRotZ.m[1][0] = (float)-sin(worldTransform_.rotation.z);
		matRotZ.m[1][1] = (float)cos(worldTransform_.rotation.z);
		// X軸回転の各要素
		matRotX.m[1][1] = (float)cos(worldTransform_.rotation.x);
		matRotX.m[1][2] = (float)sin(worldTransform_.rotation.x);
		matRotX.m[2][1] = (float)-sin(worldTransform_.rotation.x);
		matRotX.m[2][2] = (float)cos(worldTransform_.rotation.x);
		// Y軸回転の各要素
		matRotY.m[0][0] = (float)cos(worldTransform_.rotation.y);
		matRotY.m[0][2] = (float)-sin(worldTransform_.rotation.y);
		matRotY.m[2][0] = (float)sin(worldTransform_.rotation.y);
		matRotY.m[2][2] = (float)cos(worldTransform_.rotation.y);
		//平行移動
		matTrans.m[3][0] += worldTransform_.translation.x;
		matTrans.m[3][1] += worldTransform_.translation.y;
		matTrans.m[3][2] += worldTransform_.translation.z;

		//各軸用回転行列を宣言
		matRot *= matRotZ *= matRotX *= matRotY;

		worldTransform_.matWorld = Matrix4::Identity();
		worldTransform_.matWorld = matScale *= matRot *= matTrans;
	}

	Vector3 VecMat(Vector3 vec3, WorldTransform& worldTransform_)
	{
		vec3.x = (vec3.x * worldTransform_.matWorld.m[0][0]) +
				 (vec3.y * worldTransform_.matWorld.m[1][0]) +
				 (vec3.z * worldTransform_.matWorld.m[2][0]) +
				 (0 * worldTransform_.matWorld.m[3][0]);

		vec3.y = (vec3.x * worldTransform_.matWorld.m[0][1]) +
				 (vec3.y * worldTransform_.matWorld.m[1][1]) +
				 (vec3.z * worldTransform_.matWorld.m[2][1]) +
				 (0 * worldTransform_.matWorld.m[3][1]);

		vec3.z = (vec3.x * worldTransform_.matWorld.m[0][2]) +
				 (vec3.y * worldTransform_.matWorld.m[1][2]) +
				 (vec3.z * worldTransform_.matWorld.m[2][2]) +
				 (0 * worldTransform_.matWorld.m[3][2]);

		vec3.x = 10;

		return vec3;
	}

}