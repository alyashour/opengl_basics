#include <iostream>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

const char* vertex_shader_source =  "#version 330 core\n"
    "layout (position = 0) in vec3 aPos;\n"
    "void main() {\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* frag_shader_source = ""
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void render() {
    glClearColor(0.3f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
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


    // load and compile the vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertexShader);
    // check for success
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR. Vertex Shader compilation failed!\n" << infoLog << std::endl;
        return -1;
    }

    // load and compile the fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &frag_shader_source, nullptr);
    glCompileShader(fragmentShader);
    // check for success
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR. Fragment shader compilation failed!\n"  << infoLog << std::endl;
        return -1;
    }

    // create shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR. Shader Program Compilation failed!\n"  << infoLog << std::endl;
        return -1;
    }

    // delete shaders as they're no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // TRIANGLE
    // create a VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // bind the VAO

    // pass the vertices to the gpu
    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // tell opengl how to interpret the vertex data
    glVertexAttribPointer(
        0, // layout (location = 0)
        3, // we're using vec3 for the position data
        GL_FLOAT, // the datatype of the info
        GL_FALSE, // not important here
        3 * sizeof(float), // the stride of the data
        static_cast<void *>(nullptr) // pointer to where the data starts. we're at the beginning of the buffer so 0
    );

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        process_input(window);

        // render commands
        render();

        // swap buffers and poll events for next frame
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}