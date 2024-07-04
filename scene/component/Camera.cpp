#include "Camera.h"

using namespace radium;

math::Mat4x4 Camera::getViewMatrix()
{
	auto view = forward;
	view.normalize();

	auto right = view.cross(up);
	right.normalize();

	auto viewUp = right.cross(up);
	viewUp.normalize();

	//todo: opengl specific code here

	math::Mat4x4 rot(
		right.x, right.y, right.z, 1,
		viewUp.x, viewUp.y, viewUp.z, 1,
		view.x, view.y, view.z, 1,
		0,0,0,1
	);
	
	math::Vec3 xlate = -(rot * position);

	math::Mat4x4 res(rot);

	res(0, 3) = xlate.x;
	res(1, 3) = xlate.y;
	res(2, 3) = xlate.z;


	return res;


}

math::Mat4x4 Camera::getProjectionMatrix()
{
	math::Mat4x4 res;

	// todo: opengl sepcifgic code here
	float d = 1.0f / std::tan(m_fov);
	float recip = 1.0f / (m_near - m_far);

	res(0, 0) = d / m_aspect;
	res(1, 1) = d;
	res(2, 2) = (m_near + m_far) * recip;
	res(2, 3) = 2.0f * m_near * m_far * recip;
	res(3, 2) = -1.0f;
	res(3, 3) = 0.0f;

	return res;
}