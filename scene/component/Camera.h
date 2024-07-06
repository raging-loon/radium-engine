#ifndef SCENE_COMPONENT_CAMERA_H_
#define SCENE_COMPONENT_CAMERA_H_

#include "math/math.h"

namespace radium
{

#undef near
#undef far

/**
 * Camera - Virtual Camera class
 * 
 * Provides methods to get View and Projection matrices.
 * 
**/
class Camera
{
public:

	Camera(float fov, float aspect, float near, float far)
		: m_fov(glm::radians(fov)), m_aspect(aspect), m_near(near), m_far(far)
	{
		updateProjectionMatrix(aspect);
	}

	glm::vec3 position{ 0,0,-5 };

	glm::mat4x4 getViewMatrix();
	glm::mat4x4 getProjectionMatrix();

	void updateProjectionMatrix(float aspect);

	/*float m_yaw = -90.0f;
	float m_pitch = 0.0f;*/

	float m_fov;
	float m_aspect;
	
	float m_near;
	float m_far;

	glm::mat4x4 m_proj;


	static const glm::vec3 kForward;
	static const glm::vec3 kUp;
	static const glm::vec3 kRight;


};

} // radium



#endif // SCENE_COMPONENT_CAMERA_H_