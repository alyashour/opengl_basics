#include <cmath>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

float calculate_green_value() {
    const auto timeValue = static_cast<float>(glfwGetTime());
    const auto green_value = static_cast<float>((sin(timeValue) / 2.0f) + 0.5f);
    return green_value;
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    // initialize glfw
    if (!glfwInit()) {
        std::cout << "Failed to initialize glfw" << std::endl;
        glfwTerminate();
        return -1;
    }

    // set the opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window struct
    GLFWwindow* window = glfwCreateWindow(800, 600, "My Window!", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window. Error: \n" << stderr << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // initialize glad
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    // set the viewport
    glViewport(0, 0, 800, 600);

    // set the callback
    glfwSetWindowSizeCallback(window, framebuffer_size_callback);

    // create shader
    const Shader shader("shaders/basic.vert", "shaders/basic.frag");

    // TRIANGLE
    // create a VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // bind the VAO

    // vertex data
    constexpr float vertices[] = {
        // positions       // colors
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
    };

    // create a vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // index data
    constexpr unsigned int indices[] = {
        0, 1, 2, // first triangle
    };

    // create an element buffer object (EBO)
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // tell opengl how to interpret the vertex data
    glVertexAttribPointer(
        0, // layout (location = 0)
        3, // we're using vec3 for the position data
        GL_FLOAT, // the datatype of the info
        GL_FALSE, // not important here
        6 * sizeof(float), // the stride of the data
        static_cast<void *>(nullptr) // pointer to where the data starts. we're at the beginning of the buffer so 0
    );
    glEnableVertexAttribArray(0); // unbind vertex attribute array
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1); // unbind vertex attribute array

    // set shader
    shader.use();
    shader.setFloat("horizOffset", 0.2f);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        process_input(window);

        // clear the screen
        glClearColor(0.3f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render commands
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0); // unbind
        
        // swap buffers and poll events for next frame
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}