//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <math.h>

#include "camera.h"
#include "imgui.h"
#include "shader.h"

#include "model.h"

#include "load2DTexture.h"
#include "models.h"
#include "gameTextures.cpp"

#include "editModeUI.h"

const int SCR_SOURCE_WIDTH  = 1920;
const int SCR_SOURCE_HEIGHT = 1080;
const int SCR_WIDTH  = 16 * 80;
const int SCR_HEIGHT =  9 * 90;

bool editMode = false;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); // Initialization of the camera with a pos

float lastX = (float)SCR_WIDTH  / 2;
float lastY = (float)SCR_HEIGHT / 2;
bool firstMouse = false;

float deltaTime = 0.0f; // Diference of time between frames
float lastFrame = 0.0f; // Time of the last frame

float r = 0.0f; float g = 0.0f; float b = 0.0f; // BACKGROUND COLOR

void frameBufferSizeCallback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
    printf("RESIZE: %4d | %4d\n", width, height);
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        editMode = true;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        editMode = false;
}

void cursorCallBack(GLFWwindow *window, double xPos, double yPos){
    if (firstMouse){
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;
   
    if (editMode == false) camera.ProcessMouseMovement(xOffset, yOffset);
};

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset){
    camera.ProcessMouseScroll(yOffset);
}

const float *controllerAxes;
const unsigned char *controllerButtons;
bool CONTROLLER_CONNECTED = false;

void loadControllerGamePad(){
    if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GLFW_TRUE){
        int axesCount;
        int buttonCount;
        controllerAxes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
        controllerButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
        CONTROLLER_CONNECTED = true;
        printf("CONTROLLER_CONNECTED==================\n");
    }
}

void processCameraInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera.ProcessKeyboard(FORWARD , deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera.ProcessKeyboard(BACKWARD, deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { camera.ProcessKeyboard(LEFT    , deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { camera.ProcessKeyboard(RIGHT   , deltaTime); }
}

void processCameraInputController(){
    float xOffset = 0;
    float yOffset = 0;

    if (!(controllerAxes[3] < 0.5f && controllerAxes[3] > -0.5f)) xOffset = -controllerAxes[3] - lastX;
    if (!(controllerAxes[4] < 0.5f && controllerAxes[4] > -0.5f)) yOffset = lastY - (-controllerAxes[4]);
    lastX = -controllerAxes[3] * 10;
    lastY = -controllerAxes[4] * 10;
    
    camera.processController(controllerAxes, deltaTime, xOffset, yOffset);
}

void processColorScreen(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) { r += 0.01f; if (r > 1) r = 0; }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) { g += 0.01f; if (g > 1) g = 0; }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) { b += 0.01f; if (b > 1) b = 0; }

    if(glfwJoystickPresent(GLFW_JOYSTICK_1)){
        if (controllerButtons[0] == GLFW_PRESS) { g += 0.01f; if (g > 1) g = 0; } // A
        if (controllerButtons[1] == GLFW_PRESS) { b += 0.01f; if (b > 1) b = 0; } // B
        if (controllerButtons[2] == GLFW_PRESS) { r += 0.01f; if (r > 1) r = 0; } // X
    } 
}

void processAlphaBlend(GLFWwindow *window, float *alphaBlendVal){
    if (glfwGetKey(window, GLFW_KEY_UP)   == GLFW_PRESS) { *alphaBlendVal += 0.01f; if (*alphaBlendVal > 2) *alphaBlendVal = 0; }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { *alphaBlendVal -= 0.01f; if (*alphaBlendVal < 0) *alphaBlendVal = 2; }
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
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        printf("Failed to initialize GLAD");
        return -1;
    }
 
    printf("JOYSTICK/GAMEPAD 1 STATUS: %s\n", (CONTROLLER_CONNECTED == GL_TRUE)? "CONNECTED" : "DISCONECTED");
    if (CONTROLLER_CONNECTED == GL_TRUE){
        int axesCount;
        const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
        printf("NUMBER OF AXES AVAILABLE: %d\n", axesCount);
    }

    // TODO SET EDIT MODE WITH CURSOR ACTIVATION
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, cursorCallBack);
    glfwSetScrollCallback(window, scrollCallback);
    loadControllerGamePad();

    glEnable(GL_DEPTH_TEST);
    
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    printf("Maximun number of vertex attributes supported: %d\n", nrAttributes);
   
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    stbi_set_flip_vertically_on_load(true); // FLIP Y VALUE
    LoadTextures textures; 
    textures.loadAll();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // FIRST WE CREATE THE VERTEX ARRAY OBJECT THAT WILL STORE ALL THE SETTINGS
    unsigned int VAO[2], VBO[2], EBO[2]; 
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, EBO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_DYNAMIC_DRAW);

    // LIGHT VERTEX DATA LOADING
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // FLOOR VERTEX DATA LOADING
    unsigned int floorVAO, floorVBO, floorEBO;
    glGenVertexArrays(1, &floorVAO);
    glGenBuffers(1, &floorVBO);
    glGenBuffers(1, &floorEBO);
    glBindVertexArray(floorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, floorEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorIndices), floorIndices, GL_STATIC_DRAW);

    // WALL VERTES DATA LOADING
    unsigned int wallVAO, wallVBO, wallEBO;
    glGenVertexArrays(1, &wallVAO);
    glBindVertexArray(wallVAO);
    glGenBuffers(1, &wallVBO);
    glGenBuffers(1, &wallEBO);
    glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wallEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(wallIndices), wallIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // SHADER LOADING 
    Shader floorShader ("../shaders/floorVertexShader.vert" , "../shaders/floorFragmentShader.frag");
    Shader cubeShader  ("../shaders/squareVertexShader.vert", "../shaders/squareFragmentShader.frag");
    //Shader wallShader  ("../shaders/wallVertexShader.vert"  , "../shaders/wallFragmentShader.frag");
    Shader wallShader  ("../shaders/floorVertexShader.vert"  , "../shaders/floorFragmentShader.frag");
    Shader lightShader ("../shaders/lightVertexShader.vert" , "../shaders/lightFragmentShader.frag");
    Shader lightSrcShader("../shaders/lightSourceVertexShader.vert", "../shaders/lightSourceFragmentShader.frag");
    Shader materialShader("../shaders/materialVertexShader.vert", "../shaders/materialFragmentShader.frag");
    //Shader attenuationShader("../shaders/attenuationVertexShader.vert", "../shaders/attenuationFragmentShader.frag");
    Shader attenuationShader("../shaders/attenuationVertexShader.vert", "../shaders/flashFragmentShader.frag");
    Shader globalShader("../shaders/globalVertexShader.vert", "../shaders/globalFragmentShader1.frag");
    Shader modelShader("../shaders/modelVertexShader.vert", "../shaders/modelFragmentShader.frag");

    globalShader.use();
    // Directional Light
    globalShader.setVec3("dirLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
    globalShader.setVec3("dirLight.ambient" , glm::vec3(0.05f, 0.05f, 0.05f));
    globalShader.setVec3("dirLight.diffuse" , glm::vec3(0.05f, 0.05f, 0.05f));
    globalShader.setVec3("dirLight.specular", glm::vec3(0.05f, 0.05f, 0.05f));

    // Point Lights 
    globalShader.setVec3("pointLights[0].ambient" , glm::vec3(0.5f, 0.5f, 0.5f));
    globalShader.setVec3("pointLights[0].diffuse" , glm::vec3(0.5f, 0.5f, 0.5f));
    globalShader.setVec3("pointLights[0].specular", glm::vec3(0.5f, 0.5f, 0.5f));
    globalShader.setVec3("pointLights[1].ambient" , glm::vec3(0.5f, 0.5f, 0.5f));
    globalShader.setVec3("pointLights[1].diffuse" , glm::vec3(0.5f, 0.5f, 0.5f));
    globalShader.setVec3("pointLights[1].specular", glm::vec3(0.5f, 0.5f, 0.5f));
    globalShader.setVec3("pointLights[2].ambient" , glm::vec3(0.5f, 0.5f, 0.5f));
    globalShader.setVec3("pointLights[2].diffuse" , glm::vec3(0.5f, 0.5f, 0.5f));
    globalShader.setVec3("pointLights[2].specular", glm::vec3(0.5f, 0.5f, 0.5f));
    globalShader.setVec3("pointLights[3].ambient" , glm::vec3(0.5f, 0.5f, 0.5f));
    globalShader.setVec3("pointLights[3].diffuse" , glm::vec3(0.5f, 0.5f, 0.5f));
    globalShader.setVec3("pointLights[3].specular", glm::vec3(0.5f, 0.5f, 0.5f));

    globalShader.setFloat("pointLights[0].constant" , 1.0f); 
    globalShader.setFloat("pointLights[0].linear"   , 0.04f); 
    globalShader.setFloat("pointLights[0].quadratic", 0.115f); 
    globalShader.setFloat("pointLights[1].constant" , 1.0f); 
    globalShader.setFloat("pointLights[1].linear"   , 0.04f); 
    globalShader.setFloat("pointLights[1].quadratic", 0.115f); 
    globalShader.setFloat("pointLights[2].constant" , 1.0f); 
    globalShader.setFloat("pointLights[2].linear"   , 0.04f); 
    globalShader.setFloat("pointLights[2].quadratic", 0.115f); 
    globalShader.setFloat("pointLights[3].constant" , 1.0f); 
    globalShader.setFloat("pointLights[3].linear"   , 0.04f); 
    globalShader.setFloat("pointLights[3].quadratic", 0.115f); 

    glm::vec3 pointLightPositions[4] = {
        glm::vec3( 15.0f, 2.0f,  15.0f),
        //glm::vec3( 0.0f, 0.3f,  -2.0f),
        glm::vec3( 15.0f, 2.0f, -15.0f),
        glm::vec3(-15.0f, 2.0f, -15.0f),
        glm::vec3(-15.0f, 2.0f,  15.0f)
    };
    
    globalShader.setVec3("pointLights[0].position", pointLightPositions[0]);
    globalShader.setVec3("pointLights[1].position", pointLightPositions[1]);
    globalShader.setVec3("pointLights[2].position", pointLightPositions[2]);
    globalShader.setVec3("pointLights[3].position", pointLightPositions[3]);
    
    // FlashLight
    globalShader.setVec3("flashLight.ambient" , glm::vec3(1.0f, 1.0f, 1.0f));
    globalShader.setVec3("flashLight.diffuse" , glm::vec3(1.0f, 1.0f, 1.0f));
    globalShader.setVec3("flashLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    globalShader.setFloat("flashLight.constant" , 1.0f);
    globalShader.setFloat("flashLight.linear"   , 0.04f);
    globalShader.setFloat("flashLight.quadratic", 0.015f);

    globalShader.setVec3("flashLight.position", glm::vec3(0.0f, 10.0f, -2.0f));
    globalShader.setVec3("flashLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));

    glm::vec4 lightPos = glm::vec4(-5.0f, 2.0f, 0.0f, 1.0f); // changed from vec3 to vec4 to set the "w" component to change between direction and position

    glm::vec3 atteFlashConfig = glm::vec3(1.0f, 0.04f, 0.115f);
    glm::vec3 attenuationConfig = glm::vec3(1.0f, 0.04f, 0.115f);
    glm::vec3 attenuationConfig1 = glm::vec3(1.0f, 0.04f, 0.115f);
    glm::vec3 attenuationConfig2 = glm::vec3(1.0f, 0.04f, 0.115f);
    glm::vec3 attenuationConfig3 = glm::vec3(1.0f, 0.04f, 0.115f);
    glm::vec3 attenuationConfig4 = glm::vec3(1.0f, 0.04f, 0.115f);

    float flashColorLight[4] = {1, 1, 1, 1};
    float colorLightP0[4] = {1, 1, 1, 1};
    float colorLightP1[4] = {1, 1, 1, 1};
    float colorLightP2[4] = {1, 1, 1, 1};
    float colorLightP3[4] = {1, 1, 1, 1};
    
    float colorLight[4] = {1, 1, 1, 1};
    float alphaBlendVal = 0;
    bool cameraFlashlight = false;

    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;
    //ImGui_ImplGlfw_InitForOpenGL(window, true);
    //ImGui_ImplOpenGL3_Init("#version 430 core");
    //ImGui::StyleColorsDark();
    bool show_demo_window = true;
    bool pointLight1 = false;
    bool pointLight2 = false;
    bool pointLight3 = false;
    bool pointLight4 = false;

    printf("%s\n", glGetString(GL_VERSION));

    std::string backpackModelPath, teapotModelPath, caineModelPath;
    teapotModelPath = "../resources/Models/Utah_teapot/Utah-teapot.obj";
    backpackModelPath = "../resources/Models/backpack/backpack.obj";
    caineModelPath = "../resources/Models/Amazing/Caine.glb";
    Model guitar(backpackModelPath);
    Model teapot(teapotModelPath);
    //Model caine(caineModelPath);
    //
    EditMode editUI(window);

    while (!glfwWindowShouldClose(window)){
        processInput(window);
        processColorScreen(window);
        processCameraInput(window); 
        processAlphaBlend(window, &alphaBlendVal);
        
        if (CONTROLLER_CONNECTED) processCameraInputController();
        if (CONTROLLER_CONNECTED) camera.triggerAimViewFov(controllerAxes);
    
        if (editMode == true){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        glClearColor(r, g, b, 1.0f);  // This functions is a state-setting func for "glClear()"
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // State-using function 

        //ImGui_ImplOpenGL3_NewFrame();
        //ImGui_ImplGlfw_NewFrame();
        //ImGui::NewFrame();
        editUI.refreshFrame(); 

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        
        // TEXTURE BINDING 
        textures.woodBoxContainer.bindTexture(1);
        textures.pixelRedEye.bindTexture(0);
        textures.floor.bindTexture(2);
        textures.metal.bindTexture(3);
        textures.container2.bindTexture(4);
        textures.container2Spec.bindTexture(5);
        textures.matrix.bindTexture(6);
        //textures.container2WoodEmission.bindTexture(6);

        // GLOBAL VIEW & PROJECTION 
        glm::mat4 globalView       = glm::mat4(1.0f);
        glm::mat4 globalProjection = glm::mat4(1.0f);
        globalView = camera.GetViewMatrix(); 
        globalProjection = glm::perspective(glm::radians(camera.Fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
       
        // LIGHT POS ROTATION 
        globalShader.use();
        float lightAngle = 0.10f * deltaTime;
        float lPosx = lightPos.x;
        float lPosz = lightPos.z;
        lightPos.x = (cos(lightAngle) * lPosx) + (-sin(lightAngle) * lPosz);
        lightPos.z = (sin(lightAngle) * lPosx) + ( cos(lightAngle) * lPosz);
        if (lightPos.y <= -1.0f) lightPos.x = -35.0f;
        globalShader.setFloat("flashLight.cutOff", glm::cos(glm::radians(15.0f)));
        globalShader.setFloat("flashLight.outerCutOff", glm::cos(glm::radians(20.0f)));
        globalShader.setVec3("viewPos", camera.Position);

       globalShader.use();
       glm::mat4 guitarModel = glm::mat4(1.0f);
       //guitarModel = glm::translate(guitarModel, glm::vec3(-15.0f, -2.8f, 10.0f));
       guitarModel = glm::translate(guitarModel, glm::vec3(-15.0f, 0.0f, 12.0f));
       guitarModel = glm::scale    (guitarModel, glm::vec3(1.0f, 1.0f, 1.0f));
       guitarModel = glm::rotate(guitarModel, glm::radians(90.0f + currentFrame * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
       unsigned int guitarModelLoc = glGetUniformLocation(globalShader.getShaderID(), "model");
       unsigned int guitarViewLoc  = glGetUniformLocation(globalShader.getShaderID(), "view");
       unsigned int guitarProjLoc  = glGetUniformLocation(globalShader.getShaderID(), "projection");
       glUniformMatrix4fv(guitarModelLoc, 1, GL_FALSE, glm::value_ptr(guitarModel));
       glUniformMatrix4fv(guitarViewLoc , 1, GL_FALSE, glm::value_ptr(globalView));
       glUniformMatrix4fv(guitarProjLoc , 1, GL_FALSE, glm::value_ptr(globalProjection));
       guitar.draw(globalShader);
   
       globalShader.use();
       glm::mat4 teapotModel = glm::mat4(1.0f);
       //teapotModel = glm::translate(teapotModel, glm::vec3(-15.0f, -2.8f, 10.0f));
       teapotModel = glm::translate(teapotModel, glm::vec3(14.0f, -2.0f, 14.0f));
       teapotModel = glm::scale    (teapotModel, glm::vec3(9.0f, 9.0f, 9.0f));
       teapotModel = glm::rotate(teapotModel, glm::radians(90.0f + currentFrame * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
       //teapotModel = glm::rotate(teapotModel, glm::radians(currentFrame), glm::vec3(0.0f, 1.0f, 0.0f));
       unsigned int teapotModelLoc = glGetUniformLocation(globalShader.getShaderID(), "model");
       unsigned int teapotViewLoc  = glGetUniformLocation(globalShader.getShaderID(), "view");
       unsigned int teapotProjLoc  = glGetUniformLocation(globalShader.getShaderID(), "projection");
       glUniformMatrix4fv(teapotModelLoc, 1, GL_FALSE, glm::value_ptr(teapotModel));
       glUniformMatrix4fv(teapotViewLoc , 1, GL_FALSE, glm::value_ptr(globalView));
       glUniformMatrix4fv(teapotProjLoc , 1, GL_FALSE, glm::value_ptr(globalProjection));
       teapot.draw(globalShader);

       //globalShader.use();
       //glm::mat4 caineModel = glm::mat4(1.0f);
       ////caineModel = glm::translate(caineModel, glm::vec3(-15.0f, -2.8f, 10.0f));
       //caineModel = glm::translate(caineModel, glm::vec3(14.0f, -2.0f, 14.0f));
       //caineModel = glm::scale    (caineModel, glm::vec3(9.0f, 9.0f, 9.0f));
       //caineModel = glm::rotate(caineModel, glm::radians(90.0f + currentFrame * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
       ////caineModel = glm::rotate(caineModel, glm::radians(currentFrame), glm::vec3(0.0f, 1.0f, 0.0f));
       //unsigned int caineModelLoc = glGetUniformLocation(globalShader.getShaderID(), "model");
       //unsigned int caineViewLoc  = glGetUniformLocation(globalShader.getShaderID(), "view");
       //unsigned int caineProjLoc  = glGetUniformLocation(globalShader.getShaderID(), "projection");
       //glUniformMatrix4fv(caineModelLoc, 1, GL_FALSE, glm::value_ptr(caineModel));
       //glUniformMatrix4fv(caineViewLoc , 1, GL_FALSE, glm::value_ptr(globalView));
       //glUniformMatrix4fv(caineProjLoc , 1, GL_FALSE, glm::value_ptr(globalProjection));
       //caine.draw(globalShader);

        // CUBES ROTATING
        globalShader.use();
        globalShader.setInt("material.texture_diffuse1" , 4);
        globalShader.setInt("material.texture_specular1", 5);
        globalShader.setInt("material.emission", 6);

        float texMoveSpeed;
        globalShader.setFloat("time", glfwGetTime());
        //globalShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 1.0f));
        //globalShader.setVec3("lightColor" , glm::vec3(1.0f, 1.0f, 1.0f));

        glm::mat4 cubeModel = glm::mat4(1.0f);
        unsigned int modelLoc    = glGetUniformLocation(globalShader.getShaderID(), "model");
        unsigned int modelInvLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse");
        unsigned int viewLoc     = glGetUniformLocation(globalShader.getShaderID(), "view");
        unsigned int projLoc     = glGetUniformLocation(globalShader.getShaderID(), "projection");
        glUniformMatrix4fv(viewLoc , 1, GL_FALSE, glm::value_ptr(globalView));
        glUniformMatrix4fv(projLoc , 1, GL_FALSE, glm::value_ptr(globalProjection));
      
        glBindVertexArray(VAO[0]);
        for (unsigned int i = 0; i < 10; i++){
            cubeModel = glm::mat4(1.0f);
            cubeModel = glm::translate(cubeModel, cubePosition[i]);
            cubeModel = glm::scale(cubeModel, glm::vec3(0.7f, 0.7f, 0.7f));
            float angle = 20.0f * i;
            cubeModel = glm::rotate(cubeModel, glm::radians(angle + currentFrame * 15), glm::vec3(1.0f, 0.3f, 0.5f));

            glm::mat4 cubeModelInverse = glm::inverse(cubeModel); // NORMAL MATRIX
            glUniformMatrix4fv(modelInvLoc, 1, GL_FALSE, glm::value_ptr(cubeModelInverse));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
       
        // SCENARIO FLOOR
        globalShader.use();
        globalShader.setInt("material.texture_diffuse1", 2);
        globalShader.setInt("material.texture_specular1", 2);
        globalShader.setFloat("material.shininess", 16);

        glm::mat4 floorModel= glm::mat4(1.0f);
        floorModel = glm::translate(floorModel, glm::vec3(0.0f, -2.8f, 0.0f));
        glm::mat4 floorModelInv = glm::inverse(floorModel);

        unsigned int floorModelLoc = glGetUniformLocation(globalShader.getShaderID(), "model");
        unsigned int floorViewLoc  = glGetUniformLocation(globalShader.getShaderID(), "view");
        unsigned int floorProjLoc  = glGetUniformLocation(globalShader.getShaderID(), "projection");
        unsigned int floorInvModelLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse"); 
        glUniformMatrix4fv(floorModelLoc, 1, GL_FALSE, glm::value_ptr(floorModel));
        glUniformMatrix4fv(floorViewLoc , 1, GL_FALSE, glm::value_ptr(globalView));
        glUniformMatrix4fv(floorProjLoc , 1, GL_FALSE, glm::value_ptr(globalProjection));
        glUniformMatrix4fv(floorInvModelLoc, 1, GL_FALSE, glm::value_ptr(floorModelInv));
        
        glBindVertexArray(floorVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // SCENARIO WALLS
        globalShader.use();
        globalShader.setInt("material.texture_diffuse1", 2);
        globalShader.setInt("material.texture.specular1", 2);

        for (int i = 0; i < 4; i++){
            glm::mat4 wallModel= glm::mat4(1.0f);
            wallModel= glm::rotate(wallModel, glm::radians(i * 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            wallModel= glm::translate(wallModel, glm::vec3(0.0f, -2.8f, -20.0f));
            glm::mat4 wallInvModel = glm::inverse(wallModel);
            unsigned int wallInvModelLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse");
            unsigned int wallModelLoc = glGetUniformLocation(globalShader.getShaderID(), "model");
            unsigned int wallViewLoc  = glGetUniformLocation(globalShader.getShaderID(), "view");
            unsigned int wallProjLoc  = glGetUniformLocation(globalShader.getShaderID(), "projection");
            glUniformMatrix4fv(wallInvModelLoc, 1, GL_FALSE, glm::value_ptr(wallInvModel));
            glUniformMatrix4fv(wallModelLoc, 1, GL_FALSE, glm::value_ptr(wallModel));
            glUniformMatrix4fv(wallViewLoc , 1, GL_FALSE, glm::value_ptr(globalView));
            glUniformMatrix4fv(wallProjLoc , 1, GL_FALSE, glm::value_ptr(globalProjection));

            glBindVertexArray(wallVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        // SCENARIO LIGHT SOURCE 
        lightSrcShader.use();
        lightSrcShader.setVec3("lightColor", glm::vec3(colorLight[0], colorLight[1], colorLight[2]));
        glm::mat4 lightModel = glm::mat4(1.0f);

        unsigned int lightModelLoc = glGetUniformLocation(lightSrcShader.getShaderID(), "model");
        unsigned int lightViewLoc  = glGetUniformLocation(lightSrcShader.getShaderID(), "view");
        unsigned int lightProjLoc  = glGetUniformLocation(lightSrcShader.getShaderID(), "projection");
        glUniformMatrix4fv(lightViewLoc , 1, GL_FALSE, glm::value_ptr(globalView));
        glUniformMatrix4fv(lightProjLoc , 1, GL_FALSE, glm::value_ptr(globalProjection));

        for (int i = 0; i < 4; i++){
            lightModel = glm::mat4(1.0f);
            lightModel = glm::translate(lightModel, pointLightPositions[i]);
            lightModel = glm::scale(lightModel, glm::vec3(0.2f));
            glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
            glBindVertexArray(VAO[0]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        editUI.modifyShader(globalShader, camera);
        /*
        // IMGUI WINDOW BUILD 
        ImGui::Begin("EDIT MODE");
        ImGui::Checkbox("FlashLight", &cameraFlashlight);

        ImGui::SliderFloat("Flash Const", &atteFlashConfig.x, 0.0f, 2.0f);
        ImGui::SliderFloat("Flash Linear", &atteFlashConfig.y, 0.0f, 1.0f);
        ImGui::SliderFloat("Flash Quadratic", &atteFlashConfig.z, 0.0f, 1.0f);
        ImGui::ColorEdit4("FlashColor", flashColorLight);

        ImGui::Separator();
        ImGui::Checkbox("1", &pointLight1);
        ImGui::SameLine();
        ImGui::Checkbox("2", &pointLight2);
        ImGui::SameLine();
        ImGui::Checkbox("3", &pointLight3);
        ImGui::SameLine();
        ImGui::Checkbox("4", &pointLight4);

        ImGui::Separator();
        if (pointLight1){
            ImGui::Text("PointLight_1");
            ImGui::SliderFloat("Const", &attenuationConfig1.x, 0.0f, 2.0f);    
            ImGui::SliderFloat("Linear", &attenuationConfig1.y, 0.0f, 1.0f);    
            ImGui::SliderFloat("Quadratic", &attenuationConfig1.z, 0.0f, 1.0f);    
            ImGui::ColorEdit4("Color1", colorLightP0);
        }
        if (pointLight2){
            ImGui::Text("PointLight_2");
            ImGui::SliderFloat("Const", &attenuationConfig2.x, 0.0f, 2.0f);    
            ImGui::SliderFloat("Linear", &attenuationConfig2.y, 0.0f, 1.0f);    
            ImGui::SliderFloat("Quadratic", &attenuationConfig2.z, 0.0f, 1.0f);    
            ImGui::ColorEdit4("Color2", colorLightP1);
        }
        if (pointLight3){
            ImGui::SliderFloat("Const", &attenuationConfig3.x, 0.0f, 2.0f);    
            ImGui::SliderFloat("Linear", &attenuationConfig3.y, 0.0f, 1.0f);    
            ImGui::SliderFloat("Quadratic", &attenuationConfig3.z, 0.0f, 1.0f);    
            ImGui::ColorEdit4("Color3", colorLightP2);
        }
        if (pointLight4){
            ImGui::Text("PointLight_4");
            ImGui::SliderFloat("Const", &attenuationConfig4.x, 0.0f, 2.0f);    
            ImGui::SliderFloat("Linear", &attenuationConfig4.y, 0.0f, 1.0f);    
            ImGui::SliderFloat("Quadratic", &attenuationConfig4.z, 0.0f, 1.0f);    
            ImGui::ColorEdit4("Color4", colorLightP3);
        }
        ImGui::Separator();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        globalShader.use();
        globalShader.setAttenuation(attenuationConfig1, "0");
        globalShader.setAttenuation(attenuationConfig2, "1");
        globalShader.setAttenuation(attenuationConfig3, "2");
        globalShader.setAttenuation(attenuationConfig4, "3");

        globalShader.setPointColorLightN(glm::vec3(colorLightP0[0], colorLightP0[1], colorLightP0[2]), "0", "diffuse");
        globalShader.setPointColorLightN(glm::vec3(colorLightP1[0], colorLightP1[1], colorLightP1[2]), "1", "diffuse");
        globalShader.setPointColorLightN(glm::vec3(colorLightP2[0], colorLightP2[1], colorLightP2[2]), "2", "diffuse");
        globalShader.setPointColorLightN(glm::vec3(colorLightP3[0], colorLightP3[1], colorLightP3[2]), "3", "diffuse");

        globalShader.setAttenuationByStruct(atteFlashConfig, "flashLight");
        globalShader.setColorLightByStruct(glm::vec3(flashColorLight[0], flashColorLight[1], flashColorLight[2]), "flashLight", "diffuse");

        attenuationShader.use();
        attenuationShader.setAttenuation(attenuationConfig);
        attenuationShader.setVec3("light.diffuse", glm::vec3(colorLight[0], colorLight[1], colorLight[2]));
        attenuationShader.setVec3("light.ambient", glm::vec3(colorLight[0], colorLight[1], colorLight[2]));
        
        globalShader.use();
        if (cameraFlashlight){
            globalShader.setVec3("flashLight.position", camera.Position);
            globalShader.setVec3("flashLight.direction", camera.Front);
        }
        */
        // IMGUI WINDOW RENDER
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
        lastFrame = currentFrame;
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
