#include <DirectXMath.h>


namespace affinTransformation
{
	void Scale(DirectX::XMFLOAT3 scale);     //スケーリング
	void Rotate(DirectX::XMFLOAT3 rot);    //回転
	void Translate(DirectX::XMFLOAT3 pos); //移動
	void Transfer(DirectX::XMFLOAT3 fer); //上の全て		
	//void VecMat(Vector3 vec3, WorldTransform& worldTransform_);//ベクトルと行列の掛け算
}