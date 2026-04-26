#include "editModeUI.h"

EditMode::EditMode(GLFWwindow *window){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();
}

EditMode::~EditMode(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void EditMode::refreshFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void EditMode::renderUI(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditMode::modifyShader(Shader &shader, Camera &camera){

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

        shader.use();
        shader.setAttenuation(attenuationConfig1, "0");
        shader.setAttenuation(attenuationConfig2, "1");
        shader.setAttenuation(attenuationConfig3, "2");
        shader.setAttenuation(attenuationConfig4, "3");

        shader.setPointColorLightN(glm::vec3(colorLightP0[0], colorLightP0[1], colorLightP0[2]), "0", "diffuse");
        shader.setPointColorLightN(glm::vec3(colorLightP1[0], colorLightP1[1], colorLightP1[2]), "1", "diffuse");
        shader.setPointColorLightN(glm::vec3(colorLightP2[0], colorLightP2[1], colorLightP2[2]), "2", "diffuse");
        shader.setPointColorLightN(glm::vec3(colorLightP3[0], colorLightP3[1], colorLightP3[2]), "3", "diffuse");

        shader.setAttenuationByStruct(atteFlashConfig, "flashLight");
        shader.setColorLightByStruct(glm::vec3(flashColorLight[0], flashColorLight[1], flashColorLight[2]), "flashLight", "diffuse");

        
        shader.use();
        if (cameraFlashlight){
            shader.setVec3("flashLight.position", camera.Position);
            shader.setVec3("flashLight.direction", camera.Front);
        }

        // IMGUI WINDOW RENDER
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
