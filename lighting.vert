#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor; // Input color attribute

out vec3 Color; // Output color to fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0); // Set position
    Color = aColor; // Pass color to fragment shader
}
