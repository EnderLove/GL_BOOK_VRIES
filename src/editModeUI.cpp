#include "editModeUI.h"

EditMode::EditMode(GLFWwindow *window){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();
}

EditMode::~EditMode(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void EditMode::modifyShader(Shader &shader){

    /*
    ImGui::Begin("EDIT MODE");
    ImGui::Text("ATTENUATION CONFIGURATION");
    ImGui::SliderFloat("Attenuation Const" , &attenuationConfig.x, 0.0f, 2.0f);
    ImGui::SliderFloat("Attenuation Linear", &attenuationConfig.y, 0.0f, 1.0f);
    ImGui::SliderFloat("Attenuation Quad"  , &attenuationConfig.z, 0.0f, 1.0f);
    ImGui::Text("LIGHT COLOR");
    ImGui::ColorEdit4("Light Color", colorLight);
    ImGui::Checkbox("FlashLight", &cameraFlashlight);
    ImGui::End();
    
    shader.use();
    shader.setAttenuation(attenuationConfig);
    shader.setVec3("light.diffuse", glm::vec3(colorLight[0], colorLight[1], colorLight[2]));
    shader.setVec3("light.ambient", glm::vec3(colorLight[0], colorLight[1], colorLight[2]));

    shader.use();
    if (cameraFlashlight){
        shader.setVec3("flashLight.position", camera.Position);
        shader.setVec3("flashLight.direction", camera.Front);
    }

    // IMGUI WINDOW RENDER
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    */
}
