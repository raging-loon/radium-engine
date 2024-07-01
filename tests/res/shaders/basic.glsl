#section VS
#version 460

layout (location = 0) in vec3 iPosition;


layout (std140, binding=1) uniform perPass
{
	vec3 cameraPosition;
};


layout (std140, binding=2) uniform perObject
{
	mat4 modelViewProjection;
	vec4 poColor;	// 16
};

out vec4 color;

void main()
{

	gl_Position =  vec4(iPosition , 1.0f) * modelViewProjection;
	color = poColor;
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