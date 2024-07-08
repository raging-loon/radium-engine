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
	mat4 model;
	vec4 poColor;	// 16
};

out vec4 color;
out vec3 FragPos;
out vec3 Normal;
void main()
{
	gl_Position =  modelViewProjection * vec4(iPosition , 1.0f);
	color = poColor;
	// todo: fix
	Normal = mat3(transpose(inverse(model))) * iNormal;
	FragPos = vec3(model * vec4(iPosition, 1.0));
}
#endsection


#section PS

#version 460

layout (std140, binding=1) uniform perPass
{
	vec3 cameraPosition;
};


layout (std140, binding=2) uniform perObject
{
	mat4 modelViewProjection;
	mat4 model;
	vec4 poColor;	// 16
};

out vec4 FragColor;
in vec4 color;
in vec3 Normal;
in vec3 FragPos;

void main()
{

	vec3 ambientColor = vec3(1,1,1);

	vec3 ambient = ambientColor * 0.1;

	vec3 norm = normalize(Normal);
	vec3 lightPos = vec3(0, 1, -1);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1,1,1);


	vec3 viewDir = normalize(cameraPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
	vec3 specular = 0.5 * spec * vec3(1,1,1);

	vec3 res = (ambient + diffuse + specular)  * vec3(color.x,color.y, color.z) ;

	FragColor = vec4(res, 1.0f);
}

#endsection