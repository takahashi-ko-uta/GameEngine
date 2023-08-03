#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <DirectXMath.h>
#include <wrl.h>


class Camera
{
private:
	// DirectX::���ȗ�
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	void UpdeteViewMatrix();
	
	void UpdeteProjectionMatrix();
public://�A�N�Z�b�T
	//getter
	const XMMATRIX& GetMatView() const { return matView; }
	const XMMATRIX& GetMatProjection() const { return matProjection; }
	const XMMATRIX& GetMatViewProjection() { return matViewProjection; }
	const XMFLOAT3& GetEye() const { return eye; }
	const XMFLOAT3& GetTarget() const { return target; }
	const XMFLOAT3& GetUp() const { return up; }
	//setter
	void SetMatView(const XMMATRIX& matView) { this->matView = matView; }
	void SetMatProjection(const XMMATRIX& matProjection) { this->matProjection = matProjection; }
	void SetEye(const XMFLOAT3& eye) { this->eye = eye; }
	void SetTarget(const XMFLOAT3& target) { this->target = target; }
	void SetUp(const XMFLOAT3& up) { this->up = up; }

protected:
	// �r���[�s��
	XMMATRIX matView = {};
	// �ˉe�s��
	XMMATRIX matProjection = {};

	XMMATRIX matViewProjection = {};

	//ViewProjection viewProjection;

	// ���_���W
	XMFLOAT3 eye;
	// �����_���W
	XMFLOAT3 target;
	// ������x�N�g��
	XMFLOAT3 up;
};
