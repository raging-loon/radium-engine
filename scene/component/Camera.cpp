#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace radium;


const glm::vec3 Camera::kForward (0.0f, 0.0f, 1.0f);
const glm::vec3 Camera::kUp (0.0f,1.0f,0.0f);
const glm::vec3 Camera::kRight (1.0f,0.0f,0.0f);

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
	m_proj = glm::perspective(m_fov, aspect, m_near, m_far);
}
