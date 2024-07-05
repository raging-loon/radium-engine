#section VS
#version 460

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTexCoord;


layout (std140, binding=1) uniform perPass
{
	vec3 cameraPosition;
};


layout (std140, binding=2) uniform perObject
{
	mat4 modelViewProjection;
	vec3 poColor;	// 16
};

out vec4 color;
out vec3 Normal;

void main()
{
	// light direction
	gl_Position =  modelViewProjection * vec4(iPosition , 1.0f);
	color = vec4(poColor, 1.0f);
	Normal = iNormal;
}
#endsection


#section PS
#version 460

out vec4 FragColor;
in vec4 color;
in vec3 Normal;

layout (std140, binding=1) uniform perPass
{
	vec3 cameraPosition;
};


layout (std140, binding=2) uniform perObject
{
	mat4 modelViewProjection;
	vec3 poColor;	// 16
};
void main()
{	
	vec3 l = vec3(0,2,-4);
	vec3 lightColor = vec3(1,1,1);

	vec3 ccool = vec3(0, 0, 0.55) + vec3(0.25 * Normal);
	vec3 cwarm = vec3(0.3, 0.3, 0) + vec3(0.25 * Normal);
	vec3 chighlight = vec3(1,1,1);


	float t = (dot(Normal, l) + 1) / 2;

	// calculate reflection
	vec3 r = vec3(2 * ((dot(Normal,l)) * Normal) - l);

	float s = (100 * (dot(r, cameraPosition)) - 97);
	s = clamp(s, 0.0, 1.0);
	
	vec3 outColor = (s * chighlight) + (1 - s) * ((t * cwarm) + ((1 - t) * ccool));
	FragColor = vec4(outColor, 1.0f);
}

#endsection