#ifndef SCENE_COMPONENT_DEV_CAMERA_H_
#define SCENE_COMPONENT_DEV_CAMERA_H_

#include "scene/component/Camera.h"

namespace radium
{

class DevCamera : public Camera
{
public:

	DevCamera(float fov, float aspect, float near, float far)
		: Camera(fov, aspect, near, far)
	{
	}

	void update();

};


} // radium

#endif // SCENE_COMPONENT_DEV_CAMERA_H_