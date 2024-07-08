#ifndef GRAPHICS_LIGHTS_H_
#define GRAPHICS_LIGHTS_H_

#include <glm/glm.hpp>

namespace radium
{

struct DirectionalLight
{
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct PointLight
{
	glm::vec3 position;
	glm::vec4 color;

	float constant;
	float linear;
	float quadratic;

};

struct SpotLight
{

};

} // radium


#endif // GRAPHICS_LIGHTS_H_