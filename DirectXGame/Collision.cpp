#include "Collision.h"
using namespace DirectX;

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane,
	DirectX::XMVECTOR* inter)
{
	//���W�̌��_���狅�̒��S���W�ւ̋���
	XMVECTOR distV = XMVector3Dot(sphere.center, plane.normal);
	//���ʂ̌��_���������Z���邱�ƂŁA���ʂƋ��̒��S�Ƃ̋������o��
	float dist = distV.m128_f32[0] - plane.distance;
	//�����̐�Βl�����a���傫����Γ������ĂȂ�
	if (fabsf(dist) > sphere.radius)
	{
		return false;
	}
	//�^����_���v�Z
	if (inter) {
		//���ʏ�̍ŋߐړ_���A�^����_�Ƃ���
		*inter = -dist * plane.normal + sphere.center;
	}

	return true;
}

bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane,
	float* distance, DirectX::XMVECTOR* inter)
{
	const float epsilon = 1.0e-5f; //�덷�z���p�̔����Ȓl
	//�ʖ@���ƃ��C�̕����x�N�g���̓���
	float d1 = XMVector3Dot(plane.normal, ray.dir).m128_f32[0];
	//�����ɂ͓�����Ȃ�
	if (d1 > -epsilon) { return false; }
	//�n�_�ƌ��_�̋����i���ʂ̖@�������j
	//�ʖ@���ƃ��C�̎n�_���W�i�ʒu�x�N�g���j�̓���
	float d2 = XMVector3Dot(plane.normal, ray.start).m128_f32[0];
	//�n�_�ƕ��ʂ̋����i���ʂ̖@�������j
	float dist = d2 - plane.distance;
	//�n�_�ƕ��ʂ̋����i���C�����j
	float t = dist / -d1;
	//��_���n�_�����ɂ���̂ŁA������Ȃ�
	if (t < 0)return false;
	//��������������
	if (distance) { *distance = t; }
	//��_���v�Z
	if (inter) { *inter = ray.start + t * ray.dir; }
	return true;
}

bool Collision::CheckRay2Sphere(const Ray& ray, const Sphere& sphere,
	float* distance, DirectX::XMVECTOR* inter)
{
	XMVECTOR m = ray.start - sphere.center;
	float b = XMVector3Dot(m, ray.dir).m128_f32[0];
	float c = XMVector3Dot(m, m).m128_f32[0] - sphere.radius * sphere.radius;
	//lay�̎n�_��sphere�̊O���ɂ���(c < 0)�Alay��sphere���痣��Ă����������w���Ă���ꍇ(b > 0)�A������Ȃ�
	if (c > 0.0f && b > 0.0f)return false;

	float discr = b * b - c;
	//���̔��ʎ��̓��C�͋����O��Ă��邱�ƂɈ�v
	if (discr < 0.0f) { return false; }

	//���C�͋��ƌ������Ă���
	//��������ŏ��̒lt���v�Z
	float t = -b - sqrtf(discr);
	//t�����ł���ꍇ�A���C�͋��̓�������J�n���Ă���̂�t���[���ɃN�����v
	if (t > 0)t = 0.0f;
	if (distance) { *distance = 1; }

	if (inter) { *inter = ray.start + t * ray.dir; }

	return true;
}
