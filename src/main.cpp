#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#include "../include/shader.h"

const int SCR_SOURCE_WIDTH  = 1920;
const int SCR_SOURCE_HEIGHT = 1080;

const int SCR_WIDTH  = 16 * 80;
const int SCR_HEIGHT =  9 * 90;

int success;       // DEBUG VALUE
char infoLog[512]; // DEBUG BUFFER

const char *vertexShader1Source = "#version 330 core\n"
                                  "layout (location = 0) in vec3 aPos;\n"
                                  "out vec4 vertexColor;\n"
                                  "void main()\n"
                                  "{\n"
                                  "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                  "  vertexColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
                                  "}\0";

const char *vertexShader2Source = "#version 330 core\n"
                                  "layout (location = 0) in vec3 aPos;\n"
                                  "layout (location = 1) in vec3 aColor;\n"
                                  "out vec3 myColor;\n"
                                  "void main()\n"
                                  "{\n"
                                  "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                  "  myColor = aColor;\n"
                                  "}\0";


const char *fragmentShader1Source = "#version 330 core\n"
                                    "out vec4 fragColor;\n"
                                    "uniform vec4 ourColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "    fragColor = ourColor;\n"
                                    "}\0";

const char *fragmentShader2Source = "#version 330 core\n"
                                    "in vec4 vertexColor;\n"
                                    "out vec4 fragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "    fragColor = vertexColor;\n"
                                    "}\0";

const char *fragmentShader3Source = "#version 330 core\n"
                                    "in vec3 myColor;\n"
                                    "out vec4 fragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   fragColor = vec4(myColor, 1.0);\n"
                                    "}\0";


void frameBufferSizeCallback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
    printf("RESIZE: %4d | %4d\n", width, height);
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void processColorScreen(GLFWwindow *window, float *r, float *g, float *b){
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) { *r += 0.01f; if (*r > 1) *r = 0; }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) { *g += 0.01f; if (*g > 1) *g = 0; }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) { *b += 0.01f; if (*b > 1) *b = 0; }
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core-profile setting
   
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MINECRAFT KILLER (DLSS 5)", NULL, NULL);
    if (window == NULL){
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    //glfwSetWindowPos(window, SCR_SOURCE_WIDTH / 4, SCR_SOURCE_HEIGHT / 4); // TODO : Set the window at the center 
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        printf("Failed to initialize GLAD");
        return -1;
    }

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    printf("Maximun number of vertex attributes supported: %d\n", nrAttributes);
   
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
  
    float twoTriangleVertices[] = {
         0.5f,  0.5f, 0.0f,
         1.0f, -0.5f, 0.0f,
         0.0f, -0.5f, 0.0f,
         0.0f, -0.5f, 0.0f,
        -1.0f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int twoTriagIndices[] = {
        0, 1, 2,
        2, 3, 4
    };

    float triangle_1[] = {
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    float triangle_2[] = {
         0.0f, -0.5f, 0.0f,
        -1.0f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int triangleIndex[] = { 0, 1, 2 };

    float squareVertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int squareIndices[] = {
        0, 1, 3,
        1, 2, 3 
    };

    // FIRST WE CREATE THE VERTEX ARRAY OBJECT THAT WILL STORE ALL THE SETTINGS
    unsigned int VAO[2], VBO[2]; 
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    // CREATION OF THE VERTEX BUFFER OBJECT THAT WILL STORE ALL THE VERTEX DATA
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_1), triangle_1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_2), triangle_2, GL_STATIC_DRAW);

    // WE SPECIFY HOW THE GPU SHOULD READ THE DATA USING THE (VERTEX ATTRIBUTE POINTER) AND THE WE ENABLE IT
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // CREATION OF THE ELEMENT BUFFER OBJECT THAT WILL STORE THE twoTriagIndices OF THE VERTICES
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangleIndex), triangleIndex, GL_STATIC_DRAW);

    Shader interpolShader("../shaders/interpolationVertex.vert",
                          "../shaders/interpolationFragment.frag");

    Shader uniformTestShader("../shaders/testUniformVertexShader.vert",
                             "../shaders/testUniformFragmentShader.frag");

    Shader myShader("../shaders/vertexTemp.vs", "../shaders/fragmentTemp.fs");

    float r = 0; float g = 0; float b = 0;

    while (!glfwWindowShouldClose(window)){
        processInput(window);
        processColorScreen(window, &r, &g, &b);
       
        glClearColor(r, g, b, 1.0f);  // This functions is a state-setting func for "glClear()"
        glClear(GL_COLOR_BUFFER_BIT); // State-using function 
       
        float timeValue = glfwGetTime();
        
        // FIRST TRIANGLE
        interpolShader.use();
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
      
        // SECOND TRIANGLE
        uniformTestShader.use(); 
        float greenVal = (sin(timeValue) / 2) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(uniformTestShader.getShaderID(), "ourColor");
        glUniform4f(vertexColorLocation, 0.0, greenVal, 0.0, 1.0);
        
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
