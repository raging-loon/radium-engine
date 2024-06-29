#include "Camera.h"

using namespace radium;

math::Mat4x4 Camera::getViewMatrix()
{
	auto& right		= math::Vec3::RIGHT;
	auto& up		= math::Vec3::UP;
	auto& forward   = math::Vec3::BACK;



	float t0 = -(right.dot(position));
	float t1 = -(up.dot(position));
	float t2 = -(forward.dot(position));


	return math::Mat4x4(right.x, right.y, right.x, t0,
		up.x, up.y, up.z, t1,
		forward.x, forward.y, forward.z, t2,
		0, 0, 0, 1);
}

math::Mat4x4 Camera::getProjectionMatrix()
{
	auto m00 = 1 / (m_aspect * std::tanf(m_fov / 2));
	auto m11 = 1 / (std::tanf(m_fov / 2));
	auto m22 = (m_far + m_near) / (m_near - m_far);
	auto m23 = (2 * m_far * m_near) / (m_near - m_far);

	return math::Mat4x4(
		m00,  0,   0,   0,
		0,	m11,   0,   0,
		0,	  0, m22, m23,
		0,	  0,  -1,   0
	);
}
