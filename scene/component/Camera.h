#ifndef SCENE_COMPONENT_CAMERA_H_
#define SCENE_COMPONENT_CAMERA_H_

#include "math/math.h"

namespace radium
{

#undef near
#undef far


class Camera
{
public:

	Camera(float fov, float aspect, float near, float far)
		: m_fov(glm::radians(fov)), m_aspect(aspect), m_near(near), m_far(far)
	{

	}

	glm::vec3 position{ 0,0,-5 };

	glm::mat4x4 getViewMatrix();
	glm::mat4x4 getProjectionMatrix();



private:
	float m_fov = 90.0f;
	/*float m_yaw = -90.0f;
	float m_pitch = 0.0f;*/
	float m_aspect = 0.0f;
	float m_near = 0.0f;
	float m_far = 0.0f;

	static const glm::vec3 kForward;
	static const glm::vec3 kUp;
	static const glm::vec3 kRight;
};

} // radium



#endif // SCENE_COMPONENT_CAMERA_H_