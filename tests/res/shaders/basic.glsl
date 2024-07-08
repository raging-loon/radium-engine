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
out vec2 TexCoord;
void main()
{
	gl_Position =  modelViewProjection * vec4(iPosition , 1.0f);
	color = poColor;
	// todo: fix
	Normal = mat3(transpose(inverse(model))) * iNormal;
	FragPos = vec3(model * vec4(iPosition, 1.0));
	TexCoord = iTexCoord;
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
in vec2 TexCoord;

uniform sampler2D testTexture;


void main()
{

	vec3 ambientColor = vec3(1,1,1);

	vec3 ambient = ambientColor * 0.1;

	vec3 norm = normalize(Normal);
	vec3 lightPos = cameraPosition;
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1,1,1);


	vec3 viewDir = normalize(cameraPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
	vec3 specular = 0.5 * spec * vec3(1,1,1);

	vec3 res = (ambient + diffuse + specular);
	vec4 temp = texture(testTexture, TexCoord);
	FragColor = vec4(res,1.0f) * temp;
}

#endsection