#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;


out vec3 Color; 

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    if(aPos[0]==0.5)
     Color = vec3(0.0, 1.0, 0.0);
    else
    Color=vec3(1.0, 0.0, 0.0);
}
