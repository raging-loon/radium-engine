#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace radium;

glm::mat4x4 Camera::getViewMatrix()
{
	
	return  { glm::lookAt(position, position + kForward, kUp) };

}

glm::mat4x4 Camera::getProjectionMatrix()
{
	return m_proj;
}

void radium::Camera::updateProjectionMatrix(float aspect)
{
	m_proj = glm::perspective(fov, aspect, near, far);
}
