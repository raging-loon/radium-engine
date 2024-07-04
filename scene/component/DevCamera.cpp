#include "DevCamera.h"
#include "core/input/Input.h"

#include <glm/gtc/matrix_transform.hpp>

using radium::DevCamera;


void DevCamera::update()
{
	if (Input::isKeyPressed('W'))
		position.z += 0.1;
	else if (Input::isKeyPressed('S'))
		position.z -= 0.1;
	if (Input::isKeyPressed('A'))
		position.x += 0.1;
	else if (Input::isKeyPressed('D'))
		position.x -= 0.1;

}

