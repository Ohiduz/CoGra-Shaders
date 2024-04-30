#version 330 core
layout (location = 0) in vec3 aPos; // Vertex position attribute

// Uniforms
uniform mat4 model; // Model matrix
uniform mat4 view; // View matrix
uniform mat4 projection; // Projection matrix

void main()
{
    
    // Define the rotation angle in radians
    float angle = radians(69.0f);
    
    // Create rotation matrix around the Z-axis
    mat4 rotation = mat4(cos(angle), -sin(angle), 0.0, 0.0,
                         sin(angle),  cos(angle), 0.0, 0.0,
                         0.0,          0.0,         1.0, 0.0,
                         0.0,          0.0,         0.0, 1.0);


    // Define scaling factors
    vec3 scale = vec3(1.5, 0.5, 0.5);
    
    // Define translation vector
    vec3 translation = vec3(0.0, 0.5, 0.0);
    
    // Combine scaling, rotation, and translation into a single transformation matrix

    mat4 transform = mat4(1.0); // Initialize as identity matrix
    transform = mat4(
        scale.x, 0.0,      0.0,      0.0,
        0.0,     scale.y,  0.0,      0.0,
        0.0,     0.0,      scale.z,  0.0,
        0.0,     0.0,      0.0,      1.0
    ) ;
    transform[3] = vec4(translation, 1.0);

    
    gl_Position = rotation*transform * vec4(aPos, 1.0);
}
