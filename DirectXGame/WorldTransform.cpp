#include "WorldTransform.h"
#include "DirectXCommon.h"
#include <d3dx12.h>
#include "D3D12Common.h"

void WorldTransform::Initialize()
{
	CreateBuffer(constBuffer.GetAddressOf(), &constMap, (sizeof(ConstBufferData) + 0xff) & ~0xff);
}

void WorldTransform::Update()
{
	Matrix4 matScale = Matrix4::Scale(scale);
	Matrix4 matRot = Matrix4::Rotate(rotation);
	Matrix4 matTrans = Matrix4::Translate(translation);
	matWorld = matScale * matRot * matTrans;
	//eŽqŠÖŒW‚ª‚ ‚Á‚½‚ç’Ç‰Á
	if (parent) { matWorld *= parent->matWorld; }

	constMap->w = matWorld;
}
