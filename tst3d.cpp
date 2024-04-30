#include<iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<GLFW/glfw3.h>
#include<math.h>
#include<string.h>
#include<fstream>
#include<sstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;

const char* vertexShaderSourceFilePath = "./transRotAndScale.vert";
const char* fragmentShaderSourceFilePath = "./projection.frag";

const char* vertexShaderSource;
//Fragment Shader source code
const char* fragmentShaderSource;


std::string readShaderFile(const char* filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    return shaderStream.str();
}

int main()
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using 
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
    GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, 800, 800);


    string tmpvss = readShaderFile(vertexShaderSourceFilePath);
    vertexShaderSource = tmpvss.c_str();
    string tmpfss = readShaderFile(fragmentShaderSourceFilePath);
    fragmentShaderSource = tmpfss.c_str();


    // Create Vertex Shader Object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);

    // Create Shader Program Object and get its reference
    GLuint shaderProgram = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(shaderProgram);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = {
        // positions        // texture coords
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right    
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right              
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left 
        // Back face
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left     
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right        
        // Top face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom-left       
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left     
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right                
        // Bottom face
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // top-right
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // top-left     
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left        
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // bottom-right        
        // Right face
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // top-right        
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left                
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // bottom-left        
        // Left face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left        
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right                
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f  // bottom-right
    };

    unsigned int indices[] = {
        0,  1,  2,  2,  3,  0, // Front face
        4,  5,  6,  6,  7,  4, // Back face
        8,  9,  10, 10, 11, 8, // Top face
        12, 13, 14, 14, 15, 12, // Bottom face
        16, 17, 18, 18, 19, 16, // Right face
        20, 21, 22, 22, 23, 20  // Left face
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    // Load and create a texture
    // GLuint texture;
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);

    // // Set texture wrapping parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // // Set texture filtering parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // Flip texture vertically to match OpenGL's coordinate system
    unsigned char* data = stbi_load("table.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glm::mat4 model = glm::mat4(1.0f); // Initialize model matrix as identity matrix
    // Projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f);
    // View matrix
    glm::mat4 view = glm::lookAt(glm::vec3(3.0f, 2.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");

    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    // Set the view matrix uniform
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input handling
        // processInput(window);

        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable depth testing
        glEnable(GL_DEPTH_TEST);

        // Bind texture
        // glBindTexture(GL_TEXTURE_2D, texture);

        // Use shader program
        glUseProgram(shaderProgram);


        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));


        // Bind vertex array
        glBindVertexArray(VAO);

        // Draw the cube
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    // glDeleteTextures(1, &texture);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
