#version 330 core
out vec4 FragColor;

void main()
{
    // Define the color based on fragment position
    float red = gl_FragCoord.x / 800.0; // Normalize x-coordinate
    float green = gl_FragCoord.y / 600.0; // Normalize y-coordinate
    float blue = 0.4; // Set a constant blue component

    // Set the final color
    FragColor = vec4(red, green, blue, 1.0);
}
