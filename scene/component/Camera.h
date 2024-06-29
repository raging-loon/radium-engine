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
		: m_fov(fov), m_aspect(aspect), m_near(near), m_far(far)
	{

	}

	math::Vec3 position{ 0,0,-10 };

	math::Mat4x4 getViewMatrix();
	math::Mat4x4 getProjectionMatrix();
private:
	float m_fov = 90.0f;
	/*float m_yaw = -90.0f;
	float m_pitch = 0.0f;*/
	float m_aspect = 0.0f;
	float m_near = 0.0f;
	float m_far = 0.0f;

	math::Vec3 forward  = math::Vec3::BACK;
	math::Vec3 up		= math::Vec3::UP;
	math::Vec3 right	= math::Vec3::RIGHT;
};

} // radium



#endif // SCENE_COMPONENT_CAMERA_H_