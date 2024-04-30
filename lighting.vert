#version 330 core
layout (location = 0) in vec3 aPos;      // Vertex position attribute
layout (location = 1) in vec3 aNormal;   // Vertex normal attribute

out vec3 FragPos;   // Fragment position in world coordinates
out vec3 Normal;    // Normal direction in world coordinates

// Uniforms
uniform mat4 model; // Model matrix
uniform mat4 view;  // View matrix
uniform mat4 projection;  // Projection matrix

void main()
{
    vec4 viewPos = view * model * vec4(aPos, 1.0);
    FragPos = viewPos.xyz;
    Normal = mat3(transpose(inverse(view * model))) * aNormal;
    gl_Position = projection * viewPos;
}
