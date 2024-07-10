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


constexpr float DEFAULT_CAMERA_SENSITIVITY = 0.5;
constexpr glm::vec3 DEFAULT_CAMERA_POSITION = {0,0,-5};
constexpr float DEFAULT_CAMERA_NEAR = 0.1;
constexpr float DEFAULT_CAMERA_FAR = 100.0f;
constexpr float DEFAULT_CAMERA_FOV = 90.0f;

class Camera
{
public:

	Camera(
		float aspect,
		glm::vec3 nposition = DEFAULT_CAMERA_POSITION,
		float sensitivity = DEFAULT_CAMERA_SENSITIVITY,
		float fov = DEFAULT_CAMERA_FOV,
		float near = DEFAULT_CAMERA_NEAR,
		float far = DEFAULT_CAMERA_NEAR
	) 
		: fov(glm::radians(fov)), aspect(aspect), near(near), far(far),
		  yaw(0), pitch(0), sensitivity(DEFAULT_CAMERA_SENSITIVITY)
	{

	}


	Camera(float fov, float aspect, float near, float far)
		: fov(glm::radians(fov)), aspect(aspect), near(near), far(far),
		  yaw(0), pitch(0), sensitivity(DEFAULT_CAMERA_SENSITIVITY)
	{	
		
		updateProjectionMatrix(aspect);
	}

	Camera(float fov, float aspect, float near, float far, float nsensitivity)
		:  Camera(fov, aspect, near, far)
	{
		sensitivity = nsensitivity;
	}


	glm::mat4x4 getViewMatrix();
	glm::mat4x4 getProjectionMatrix();

	void updateProjectionMatrix(float aspect);

	glm::vec3 position{ 0,0,-5 };

	float fov;
	float aspect;
	
	float near;
	float far;

	float yaw = 0.0f;
	float pitch = 0.0f;

	float sensitivity;

protected:
	glm::mat4x4 m_proj;


	glm::vec3 kForward { 0.0f, 0.0f, 1.0f };
	glm::vec3 kUp{ 0.0f,1.0f,0.0f };
	glm::vec3 kRight{ 1.0f,0.0f,0.0f };


};

} // radium



#endif // SCENE_COMPONENT_CAMERA_H_