#include "DevCamera.h"
#include "core/input/Input.h"

#include <glm/gtc/matrix_transform.hpp>

using radium::DevCamera;


void DevCamera::update()
{
	if (Input::isKeyPressed('W'))
		position += kForward * sensitivity;
	else if (Input::isKeyPressed('S'))
		position -= kForward * sensitivity;
	if (Input::isKeyPressed('A'))
		position -= glm::normalize(glm::cross(kForward, kUp)) * sensitivity;
	else if (Input::isKeyPressed('D'))
		position += glm::normalize(glm::cross(kForward, kUp)) * sensitivity;
	updateRotation(0, 0);
}

void DevCamera::updateRotation(float x, float y)
{

	auto npos = Input::getMousePosition();

	x = npos.x;
	y = npos.y;

	bool clamped = false;
	if (x <= 0)
	{
		x = 783;
		clamped = true;
	}
	// (784,561)
	else if (x >= 783)
	{
		x = 0;
		clamped = true;
	} 
	if (y >= 560)
	{
		y = 0;
		clamped = true;

	}
	else if (y <= 0)
	{ 
		y = 561;
		clamped = true;
	
	}
	if (clamped)
	{
		POINT p{ x,y };
		ClientToScreen(GetForegroundWindow(), &p);
		SetCursorPos(p.x, p.y);
		lastXVal = x;
		lastYVal = y;
		return;
	}


	if ((x == lastXVal) && (y == lastYVal))
		return;

	if (lastXVal == -1)
	{
		lastXVal = x;
		lastYVal = y;
	}



	float xoffset = x - lastXVal;
	float yoffset = lastYVal - y;
	
	lastXVal = x;
	lastYVal = y;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	glm::vec3 nfront;

	nfront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	nfront.y = -sin(glm::radians(pitch));
	nfront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	kForward = glm::normalize(nfront);

}

