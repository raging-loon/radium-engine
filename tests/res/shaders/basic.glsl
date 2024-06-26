#section VS
#version 460

layout (location = 0) in vec3 iPosition;

out vec4 color;

void main()
{
	gl_Position = vec4(iPosition, 1.0f);
	color = vec4(0.5, 0.0, 0.0, 1.0);
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