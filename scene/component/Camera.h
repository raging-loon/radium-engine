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

	math::Vec3 position{ 0,0,-5 };

	math::Mat4x4 getViewMatrix();
	math::Mat4x4 getProjectionMatrix();
private:
	float m_fov = 90.0f;
	/*float m_yaw = -90.0f;
	float m_pitch = 0.0f;*/
	float m_aspect = 0.0f;
	float m_near = 0.0f;
	float m_far = 0.0f;

	static const math::Vec3 kForward;
	static const math::Vec3 kUp;
	static const math::Vec3 kRight;
};

} // radium



#endif // SCENE_COMPONENT_CAMERA_H_