#include <DirectXMath.h>


namespace affinTransformation
{
	void Scale(DirectX::XMFLOAT3 scale);     //�X�P�[�����O
	void Rotate(DirectX::XMFLOAT3 rot);    //��]
	void Translate(DirectX::XMFLOAT3 pos); //�ړ�
	void Transfer(DirectX::XMFLOAT3 fer); //��̑S��		
	//void VecMat(Vector3 vec3, WorldTransform& worldTransform_);//�x�N�g���ƍs��̊|���Z
}