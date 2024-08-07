#section VS
#version 460

layout (location = 0) in vec3 iPosition;

layout (std140, binding=2) uniform perObject
{
	mat4 modelViewProjection;
//	mat4 model;
	vec4 poColor;	// 16
};

layout (std140, binding=1) uniform perPass
{
	vec3 cameraPosition;
};

layout (std140, binding=4) uniform testData
{
	float multiplier;
};

out vec4 color;

void main()
{

	gl_Position =  vec4(iPosition , 1.0f) * modelViewProjection;

	vec4 temp = poColor;

	temp *= multiplier;

	color = temp;
}
#endsection


#section PS

#version 460

out vec4 FragColor;
in vec4 color;

void main()
{
	FragColor = color;
}

#endsection