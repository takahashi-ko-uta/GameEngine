#include "Collision.h"
using namespace DirectX;

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane,
	DirectX::XMVECTOR* inter)
{
	//座標の原点から球の中心座標への距離
	XMVECTOR distV = XMVector3Dot(sphere.center, plane.normal);
	//平面の原点距離を減算することで、平面と級の中心との距離が出る
	float dist = distV.m128_f32[0] - plane.distance;
	//距離の絶対値が半径より大きければ当たってない
	if (fabsf(dist) > sphere.radius)
	{
		return false;
	}
	//疑似交点を計算
	if (inter) {
		//平面上の最近接点を、疑似交点とする
		*inter = -dist * plane.normal + sphere.center;
	}

	return true;
}

bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane,
	float* distance, DirectX::XMVECTOR* inter)
{
	const float epsilon = 1.0e-5f; //誤差吸収用の微小な値
	//面法線とレイの方向ベクトルの内積
	float d1 = XMVector3Dot(plane.normal, ray.dir).m128_f32[0];
	//内側には当たらない
	if (d1 > -epsilon) { return false; }
	//始点と原点の距離（平面の法線方向）
	//面法線とレイの始点座標（位置ベクトル）の内積
	float d2 = XMVector3Dot(plane.normal, ray.start).m128_f32[0];
	//始点と平面の距離（平面の法線方向）
	float dist = d2 - plane.distance;
	//始点と平面の距離（レイ方向）
	float t = dist / -d1;
	//交点が始点より後ろにあるので、当たらない
	if (t < 0)return false;
	//距離を書き込む
	if (distance) { *distance = t; }
	//交点を計算
	if (inter) { *inter = ray.start + t * ray.dir; }
	return true;
}

bool Collision::CheckRay2Sphere(const Ray& ray, const Sphere& sphere,
	float* distance, DirectX::XMVECTOR* inter)
{
	XMVECTOR m = ray.start - sphere.center;
	float b = XMVector3Dot(m, ray.dir).m128_f32[0];
	float c = XMVector3Dot(m, m).m128_f32[0] - sphere.radius * sphere.radius;
	//layの始点はsphereの外側にあり(c < 0)、layがsphereから離れていく方向を指している場合(b > 0)、当たらない
	if (c > 0.0f && b > 0.0f)return false;

	float discr = b * b - c;
	//負の判別式はレイは球を外れていることに一致
	if (discr < 0.0f) { return false; }

	//レイは球と交差している
	//交差する最小の値tを計算
	float t = -b - sqrtf(discr);
	//tが負である場合、レイは球の内側から開始しているのでtをゼロにクランプ
	if (t > 0)t = 0.0f;
	if (distance) { *distance = 1; }

	if (inter) { *inter = ray.start + t * ray.dir; }

	return true;
}
