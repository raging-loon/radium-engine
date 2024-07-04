#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace radium;


const math::Vec3 Camera::kForward (0.0f, 0.0f, 1.0f);
const math::Vec3 Camera::kUp (0.0f,1.0f,0.0f);
const math::Vec3 Camera::kRight (1.0f,0.0f,0.0f);

math::Mat4x4 Camera::getViewMatrix()
{
	
	return  { glm::lookAt(position, position + kForward, kUp) };

}

math::Mat4x4 Camera::getProjectionMatrix()
{
	return { glm::perspective(m_fov, m_aspect, m_near, m_far) };
}