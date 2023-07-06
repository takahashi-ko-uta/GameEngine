#include "Camera.h"
#include "WinApp.h"

using namespace DirectX;

void Camera::Initialize()
{
	const float distance = 50.0f;

	eye = { 0,0,-distance };
	target = { 0,0,0 };
	up = { 0,1,0 };

	//�r���[�s��̌v�Z
	UpdeteViewMatrix();
	//�������e
	UpdeteProjectionMatrix();
}

void Camera::Update()
{
	//�r���[�s��̌v�Z
	UpdeteViewMatrix();
	//�������e
	UpdeteProjectionMatrix();
}

void Camera::UpdeteViewMatrix()
{
	//�r���[�s��̌v�Z
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void Camera::UpdeteProjectionMatrix()
{
	//�������e
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WinApp::window_width / (float)WinApp::window_height,
		0.1f, 1000.0f
	);
}
