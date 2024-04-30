#version 330 core
layout (location = 0) in vec3 aPos; // Vertex position attribute
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

// Uniforms
uniform mat4 model; // Model matrix
uniform mat4 view; // View matrix
uniform mat4 projection; // Projection matrix

void main()
{
    // Define the rotation axis (normalized)
    vec3 axis = normalize(vec3(1.0, 0.0, 0.0)); // Example: arbitrary axis
    
    // Define the rotation angle in radians
    float angle = radians(0.0f);
    
    // Compute sine and cosine of the angle
    float c = cos(angle);
    float s = sin(angle);
    float oc = 1.0 - c;
    
    // Compute components of the rotation matrix
    float ax = axis.x;
    float ay = axis.y;
    float az = axis.z;
    
    // Create rotation matrix around the arbitrary axis
    mat4 rotation = mat4(
        oc * ax * ax + c,         oc * ax * ay - az * s, oc * ax * az + ay * s, 0.0,
        oc * ax * ay + az * s, oc * ay * ay + c,         oc * ay * az - ax * s, 0.0,
        oc * ax * az - ay * s, oc * ay * az + ax * s, oc * az * az + c,         0.0,
        0.0,                     0.0,                     0.0,                     1.0
    );

    // Define scaling factors
    vec3 scale = vec3(1.0, 1.0, 1.0);
    
    // Define translation vector
    vec3 translation = vec3(0.0, 0.0, 0.0);
    
    // Combine scaling, rotation, and translation into a single transformation matrix
    mat4 transform = mat4(1.0); // Initialize as identity matrix
    transform = mat4(
        scale.x, 0.0,      0.0,      0.0,
        0.0,     scale.y,  0.0,      0.0,
        0.0,     0.0,      scale.z,  0.0,
        0.0,     0.0,      0.0,      1.0
    );
    transform[3] = vec4(translation, 1.0);
    
    gl_Position = projection * view * transform * rotation * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
