#ifndef GLOBAL_SHADER_INIT_CONFIG_H
#define GLOBAL_SHADER_INIT_CONFIG_H

#include "shader.h"

void InitialGlobalShaderConfig(Shader &shader){
    shader.use();
    // Directional Light
    shader.setVec3("dirLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
    shader.setVec3("dirLight.ambient" , glm::vec3(0.03f, 0.03f, 0.03f));
    shader.setVec3("dirLight.diffuse" , glm::vec3(0.03f, 0.03f, 0.03f));
    shader.setVec3("dirLight.specular", glm::vec3(0.03f, 0.03f, 0.03f));

    // Point Lights 
    shader.setVec3("pointLights[0].ambient" , glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVec3("pointLights[0].diffuse" , glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVec3("pointLights[0].specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVec3("pointLights[1].ambient" , glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVec3("pointLights[1].diffuse" , glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVec3("pointLights[1].specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVec3("pointLights[2].ambient" , glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVec3("pointLights[2].diffuse" , glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVec3("pointLights[2].specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVec3("pointLights[3].ambient" , glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVec3("pointLights[3].diffuse" , glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVec3("pointLights[3].specular", glm::vec3(0.5f, 0.5f, 0.5f));

    shader.setFloat("pointLights[0].constant" , 1.0f); 
    shader.setFloat("pointLights[0].linear"   , 0.04f); 
    shader.setFloat("pointLights[0].quadratic", 0.115f); 
    shader.setFloat("pointLights[1].constant" , 1.0f); 
    shader.setFloat("pointLights[1].linear"   , 0.04f); 
    shader.setFloat("pointLights[1].quadratic", 0.115f); 
    shader.setFloat("pointLights[2].constant" , 1.0f); 
    shader.setFloat("pointLights[2].linear"   , 0.04f); 
    shader.setFloat("pointLights[2].quadratic", 0.115f); 
    shader.setFloat("pointLights[3].constant" , 1.0f); 
    shader.setFloat("pointLights[3].linear"   , 0.04f); 
    shader.setFloat("pointLights[3].quadratic", 0.115f); 

    glm::vec3 pointLightPositions[4] = {
        glm::vec3( 15.0f, 2.0f,  15.0f),
        //glm::vec3( 0.0f, 0.3f,  -2.0f),
        glm::vec3( 15.0f, 2.0f, -15.0f),
        glm::vec3(-15.0f, 2.0f, -15.0f),
        glm::vec3(-15.0f, 2.0f,  15.0f)
    };
    
    shader.setVec3("pointLights[0].position", pointLightPositions[0]);
    shader.setVec3("pointLights[1].position", pointLightPositions[1]);
    shader.setVec3("pointLights[2].position", pointLightPositions[2]);
    shader.setVec3("pointLights[3].position", pointLightPositions[3]);
    
    // FlashLight
    shader.setVec3("flashLight.ambient" , glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setVec3("flashLight.diffuse" , glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setVec3("flashLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    shader.setFloat("flashLight.constant" , 1.0f);
    shader.setFloat("flashLight.linear"   , 0.04f);
    shader.setFloat("flashLight.quadratic", 0.015f);

    shader.setVec3("flashLight.position", glm::vec3(0.0f, 10.0f, -10.0f));
    shader.setVec3("flashLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
}

#endif // GLOBAL_SHADER_INIT_CONFIG_H!
