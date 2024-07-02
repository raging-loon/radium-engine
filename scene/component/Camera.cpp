#include "Camera.h"

using namespace radium;
using math::Vec3;
math::Mat4x4 Camera::getViewMatrix()
{

	auto& eye = position;
	auto center = position + forward;

	auto f = Vec3::normalize(center - eye);
	auto s = Vec3::normalize(Vec3::cross(up, f));
	auto u = Vec3::cross(f, s);

	math::Mat4x4 res;

	res.m00 = s.x;
	res.m10 = s.y;
	res.m20 = s.z;
	res.m01 = u.x;
	res.m11 = u.y;
	res.m21 = u.z;
	res.m02 = f.x;
	res.m12 = f.y;
	res.m22 = f.z;
	res.m30 = - Vec3::dot(s, eye);
	res.m31 = - Vec3::dot(u, eye);
	res.m32 = - Vec3::dot(f, eye);

	return res;
}

math::Mat4x4 Camera::getProjectionMatrix()
{
	float d = 1 / std::tanf(m_fov / 2);
	float a = m_aspect;
	math::Mat4x4 res;

	res.m00 = d / a;
	res.m11 = d;
	res.m22 = (m_near + m_far) / (m_near - m_far);
	res.m23 = (2 * m_near * m_far) / (m_near - m_far);
	res.m32 = -1;
	res.m33 = 0;

	return res;
}
