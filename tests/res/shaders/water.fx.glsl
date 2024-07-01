#section VS
#version 460 core

layout (location = 0) in vec2 iPosition;
layout (location = 1) in vec2 iTexCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(iPosition, 0.0, 1.0);
    TexCoords = iTexCoords;

}

#endsection
#section PS
#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D fbo_texture;
uniform float offset;



const float doffset = 1.0 / 300.0;  

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-doffset,  doffset), // top-left
        vec2( 0.0f,    doffset), // top-center
        vec2( doffset,  doffset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( doffset,  0.0f),   // center-right
        vec2(-doffset, -doffset), // bottom-left
        vec2( 0.0f,   -doffset), // bottom-center
        vec2( doffset, -doffset)  // bottom-right    
    );

float kernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16  
);
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(fbo_texture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i] * 1.1;
    
    FragColor = vec4(col, 1.0);
}
#endsection