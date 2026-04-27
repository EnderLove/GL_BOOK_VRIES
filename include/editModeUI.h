#ifndef EDIT_MODE_UI_H
#define EDIT_MODE_UI_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "shader.h"
#include "camera.h"

#define MIN_CONST_VAL  0.0f
#define MAX_CONST_VAL  2.0f
#define MIN_LINEAR_VAL 0.0f
#define MAX_LINEAR_VAL 1.0f
#define MIN_QUAD_VAL   0.0f
#define MAX_QUAD_VAL   0.1F

class EditMode{
    private:
        ImGuiIO io;
        bool cameraFlashlight = false;

        glm::vec3 atteFlashConfig    = glm::vec3(1.0f, 0.04f, 0.115f);
        glm::vec3 attenuationConfig  = glm::vec3(1.0f, 0.04f, 0.115f);
        glm::vec3 attenuationConfig1 = glm::vec3(1.0f, 0.04f, 0.115f);
        glm::vec3 attenuationConfig2 = glm::vec3(1.0f, 0.04f, 0.115f);
        glm::vec3 attenuationConfig3 = glm::vec3(1.0f, 0.04f, 0.115f);
        glm::vec3 attenuationConfig4 = glm::vec3(1.0f, 0.04f, 0.115f);

        float directColorLight[4] = {0.03f, 0.03f, 0.03f, 0.03f};
        float flashColorLight[4]  = {1, 1, 1, 1};
        float colorLightP0[4] = {1, 1, 1, 1};
        float colorLightP1[4] = {1, 1, 1, 1};
        float colorLightP2[4] = {1, 1, 1, 1};
        float colorLightP3[4] = {1, 1, 1, 1};
        float colorLight[4] = {1, 1, 1, 1};
        
        bool pointLight1 = false;
        bool pointLight2 = false;
        bool pointLight3 = false;
        bool pointLight4 = false;

    public:
        EditMode(GLFWwindow *window);
        ~EditMode();
        
        void modifyShader(Shader &shader, Camera &camera);
        void refreshFrame();
        void renderUI();


};

#endif // !EDIT_MODE_UI_H
