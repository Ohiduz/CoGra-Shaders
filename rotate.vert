#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Define the rotation angle in radians
    float angle = radians(69.0f);
    
    // Create rotation matrix around the Z-axis
    mat4 rotation = mat4(cos(angle), -sin(angle), 0.0, 0.0,
                         sin(angle),  cos(angle), 0.0, 0.0,
                         0.0,          0.0,         1.0, 0.0,
                         0.0,          0.0,         0.0, 1.0);
    
    // Apply rotation to the model matrix
    
    
    // Set the position of the vertex
    gl_Position = rotation*vec4(aPos, 1.0);
}

