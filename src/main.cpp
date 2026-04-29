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

    // SHADER LOADING 
    Shader globalShader("../shaders/globalVertexShader.glsl", "../shaders/globalFragmentShader1.glsl");

    globalShader.use();
    // Directional Light
    globalShader.setVec3("dirLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
    globalShader.setVec3("dirLight.ambient" , glm::vec3(0.03f, 0.03f, 0.03f));
    globalShader.setVec3("dirLight.diffuse" , glm::vec3(0.03f, 0.03f, 0.03f));
    globalShader.setVec3("dirLight.specular", glm::vec3(0.03f, 0.03f, 0.03f));

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

    bool show_demo_window = true;
    bool pointLight1 = false;
    bool pointLight2 = false;
    bool pointLight3 = false;
    bool pointLight4 = false;

    printf("%s\n", glGetString(GL_VERSION));

    std::string backpackModelPath, teapotModelPath, caineModelPath, metalCubePath, scenarioModelPath, containerModelPath;
    //teapotModelPath = "../resources/Models/Utah_teapot/Utah-teapot.obj";
    teapotModelPath = "../resources/Models/Utha_Teapot/Utah-teapot.obj";
    backpackModelPath = "../resources/Models/backpack/backpack.obj";
    caineModelPath = "../resources/Models/Amazing/Caine.glb";
    metalCubePath = "../resources/Models/MetalCube/metalCube.obj";
    scenarioModelPath = "../resources/Models/Scenario01/Scenario01.obj";
    containerModelPath = "../resources/Models/Container/container.obj";
    Model guitar(backpackModelPath);
    Model teapot(teapotModelPath);
    Model metalCube(metalCubePath);
    Model scenario(scenarioModelPath);
    Model container(containerModelPath);
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

        editUI.refreshFrame(); // EDIT MODE FRAME REFRESH

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        
        // TEXTURE BINDING 
        //textures.woodBoxContainer.bindTexture(1);
        textures.pixelRedEye.bindTexture(7);
        //textures.floor.bindTexture(2);
        //textures.metal.bindTexture(3);
        textures.container2.bindTexture(4);
        textures.container2Spec.bindTexture(5);
        //textures.matrix.bindTexture(6);
        textures.container2WoodEmission.bindTexture(6);

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

        // TODO STILL NEED TO FIX THE SPECULAR EXPORT
        globalShader.use();
        glm::mat4 guitarModel = glm::mat4(1.0f);
        //guitarModel = glm::translate(guitarModel, glm::vec3(-15.0f, -2.8f, 10.0f));
        guitarModel = glm::translate(guitarModel, glm::vec3(-15.0f, 0.0f, 12.0f));
        guitarModel = glm::scale    (guitarModel, glm::vec3(1.0f, 1.0f, 1.0f));
        guitarModel = glm::rotate(guitarModel, glm::radians(90.0f + currentFrame * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 guitarModelInverse = glm::inverse(guitarModel);
        unsigned int guitarModelLoc    = glGetUniformLocation(globalShader.getShaderID(), "model");
        unsigned int guitarModelInvLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse");
        unsigned int guitarViewLoc     = glGetUniformLocation(globalShader.getShaderID(), "view");
        unsigned int guitarProjLoc     = glGetUniformLocation(globalShader.getShaderID(), "projection");
        glUniformMatrix4fv(guitarModelLoc   , 1, GL_FALSE, glm::value_ptr(guitarModel));
        glUniformMatrix4fv(guitarModelInvLoc, 1, GL_FALSE, glm::value_ptr(guitarModelInverse));
        glUniformMatrix4fv(guitarViewLoc    , 1, GL_FALSE, glm::value_ptr(globalView));
        glUniformMatrix4fv(guitarProjLoc    , 1, GL_FALSE, glm::value_ptr(globalProjection));
        guitar.draw(globalShader);
    
        globalShader.use();
        globalShader.setFloat("material.shininess", 256);
        glm::mat4 teapotModel = glm::mat4(1.0f);
        teapotModel = glm::translate(teapotModel, glm::vec3(14.0f, -2.0f, 14.0f));
        teapotModel = glm::scale    (teapotModel, glm::vec3(9.0f, 9.0f, 9.0f));
        teapotModel = glm::rotate(teapotModel, glm::radians(90.0f + currentFrame * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 teapotModelInverse = glm::inverse(teapotModel); // NORMAL MATRIX
        //teapotModel = glm::rotate(teapotModel, glm::radians(currentFrame), glm::vec3(0.0f, 1.0f, 0.0f));
        unsigned int teapotModelLoc    = glGetUniformLocation(globalShader.getShaderID(), "model");
        unsigned int teapotModelInvLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse"); 
        unsigned int teapotViewLoc     = glGetUniformLocation(globalShader.getShaderID(), "view");
        unsigned int teapotProjLoc     = glGetUniformLocation(globalShader.getShaderID(), "projection");
        glUniformMatrix4fv(teapotModelLoc   , 1, GL_FALSE, glm::value_ptr(teapotModel));
        glUniformMatrix4fv(teapotModelInvLoc, 1, GL_FALSE, glm::value_ptr(teapotModelInverse));
        glUniformMatrix4fv(teapotViewLoc    , 1, GL_FALSE, glm::value_ptr(globalView));
        glUniformMatrix4fv(teapotProjLoc    , 1, GL_FALSE, glm::value_ptr(globalProjection));
        teapot.draw(globalShader);

        globalShader.use();        
        globalShader.setFloat("material.shininess", 16);
        glm::mat4 metalCubeModel = glm::mat4(1.0f);
        metalCubeModel = glm::translate(metalCubeModel, glm::vec3(14.0f, -2.0f, -14.0f));
        metalCubeModel = glm::scale    (metalCubeModel, glm::vec3(1.0f, 1.0f, 1.0f));
        metalCubeModel = glm::rotate(metalCubeModel, glm::radians(90.0f + currentFrame * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 metalCubeModelInverse = glm::inverse(metalCubeModel); // NORMAL MATRIX
        unsigned int metalCubeModelLoc    = glGetUniformLocation(globalShader.getShaderID(), "model");
        unsigned int metalCubeModelInvLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse"); 
        unsigned int metalCubeViewLoc     = glGetUniformLocation(globalShader.getShaderID(), "view");
        unsigned int metalCubeProjLoc     = glGetUniformLocation(globalShader.getShaderID(), "projection");
        glUniformMatrix4fv(metalCubeModelLoc   , 1, GL_FALSE, glm::value_ptr(metalCubeModel));
        glUniformMatrix4fv(metalCubeModelInvLoc, 1, GL_FALSE, glm::value_ptr(metalCubeModelInverse));
        glUniformMatrix4fv(metalCubeViewLoc    , 1, GL_FALSE, glm::value_ptr(globalView));
        glUniformMatrix4fv(metalCubeProjLoc    , 1, GL_FALSE, glm::value_ptr(globalProjection));
        metalCube.draw(globalShader);

        globalShader.use();
        globalShader.setFloat("material.shininess", 16);
        glm::mat4 scenarioModel = glm::mat4(1.0f);
        scenarioModel = glm::translate(scenarioModel, glm::vec3(0.0f, -3.0f, 0.0f));
        scenarioModel = glm::scale    (scenarioModel, glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 scenarioModelInverse = glm::inverse(scenarioModel); // NORMAL MATRIX
        unsigned int scenarioModelLoc    = glGetUniformLocation(globalShader.getShaderID(), "model");
        unsigned int scenarioModelInvLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse"); 
        unsigned int scenarioViewLoc     = glGetUniformLocation(globalShader.getShaderID(), "view");
        unsigned int scenarioProjLoc     = glGetUniformLocation(globalShader.getShaderID(), "projection");
        glUniformMatrix4fv(scenarioModelLoc   , 1, GL_FALSE, glm::value_ptr(scenarioModel));
        glUniformMatrix4fv(scenarioModelInvLoc, 1, GL_FALSE, glm::value_ptr(scenarioModelInverse));
        glUniformMatrix4fv(scenarioViewLoc    , 1, GL_FALSE, glm::value_ptr(globalView));
        glUniformMatrix4fv(scenarioProjLoc    , 1, GL_FALSE, glm::value_ptr(globalProjection));
        scenario.draw(globalShader);

        globalShader.use();
        globalShader.setInt("material.texture_specular1", 7);
        globalShader.setFloat("material.shininess", 16);
        glm::mat4 containerModel = glm::mat4(1.0f);
        glm::mat4 containerModelInverse = glm::inverse(containerModel); // NORMAL MATRIX
        unsigned int containerModelLoc    = glGetUniformLocation(globalShader.getShaderID(), "model");
        unsigned int containerModelInvLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse"); 
        unsigned int containerViewLoc     = glGetUniformLocation(globalShader.getShaderID(), "view");
        unsigned int containerProjLoc     = glGetUniformLocation(globalShader.getShaderID(), "projection");
        glUniformMatrix4fv(containerViewLoc    , 1, GL_FALSE, glm::value_ptr(globalView));
        glUniformMatrix4fv(containerProjLoc    , 1, GL_FALSE, glm::value_ptr(globalProjection));
       
        for (unsigned int i = 0; i < 10; i++){
            containerModel = glm::mat4(1.0f);
            containerModel = glm::translate(containerModel, cubePosition[i]);
            containerModel = glm::scale(containerModel, glm::vec3(0.5f, 0.5f, 0.5f));
            float angle = 20.0f * i;
            containerModel = glm::rotate(containerModel, glm::radians(angle + currentFrame * 15), glm::vec3(1.0f, 0.3f, 0.5f));
            containerModelInverse = glm::inverse(containerModel); // NORMAL MATRIX
            glUniformMatrix4fv(containerModelInvLoc, 1, GL_FALSE, glm::value_ptr(containerModelInverse));
            glUniformMatrix4fv(containerModelLoc, 1, GL_FALSE, glm::value_ptr(containerModel));
            container.draw(globalShader);
        }
 
        // SCENARIO LIGHT SOURCE 
        globalShader.use();
        globalShader.setBool("pointLightSource", 1);
        glm::mat4 lightModel = glm::mat4(1.0f);

        unsigned int lightModelLoc = glGetUniformLocation(globalShader.getShaderID(), "model");
        unsigned int lightViewLoc  = glGetUniformLocation(globalShader.getShaderID(), "view");
        unsigned int lightProjLoc  = glGetUniformLocation(globalShader.getShaderID(), "projection");
        glUniformMatrix4fv(lightViewLoc , 1, GL_FALSE, glm::value_ptr(globalView));
        glUniformMatrix4fv(lightProjLoc , 1, GL_FALSE, glm::value_ptr(globalProjection));

        for (int i = 0; i < 4; i++){
            globalShader.setInt("nPointLight", i);
            lightModel = glm::mat4(1.0f);
            lightModel = glm::translate(lightModel, pointLightPositions[i]);
            lightModel = glm::scale(lightModel, glm::vec3(0.07f));
            glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
            metalCube.draw(globalShader);
        }
        globalShader.setBool("pointLightSource", 0); // RESET VALUE
        
        editUI.modifyShader(globalShader, camera); // ACTUAL UI
        editUI.renderUI(); // RENDER UI        

        glfwSwapBuffers(window);
        glfwPollEvents();
        lastFrame = currentFrame;
    }
    glfwTerminate();
    return 0;
}
