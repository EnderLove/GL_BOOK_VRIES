#ifndef SCENE_H
#define SCENE_H

// Scene
// - Models
// - Shader
// TODO: Model paths could be an Array;
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "camera.h"
#include "shader.h"
#include "load2DTexture.h"
#include "../src/gameTextures.cpp"

const int SCR_WIDTH  = 16 * 80;
const int SCR_HEIGHT =  9 * 90;

class Scene{
    private:
         Camera *camera;
         std::string metalCubePath;
         std::string scenarioModelPath;
         std::string containerModelPath;
       
         LoadTextures textures;

         Model *metalCube;
         Model *scenario;
         Model *container;

         glm::vec3 pointLightPositions[4];
         float yPos;

    public:
        Scene(Camera *camera){
            this->camera = camera;

            //camera(glm::vec3(0.0f, 3.0f, 3.0f));
            metalCubePath = "../resources/Models/PhysicsCube/PhysicsCube.obj";
            scenarioModelPath = "../resources/Models/PhysicsFloor/PhysicsFloor.obj";
            containerModelPath = "../resources/Models/Container/container.obj";

            metalCube = new Model(metalCubePath);
            scenario  = new Model(scenarioModelPath);
            container = new Model(containerModelPath);

            textures.loadAll();
            pointLightPositions[0]  = glm::vec3( 15.0f, 2.0f,  15.0f);
            //glm::vec3( 0.0f, 0.3f,  -2.0f),
            pointLightPositions[1] = glm::vec3( 15.0f, 2.0f, -15.0f);
            pointLightPositions[2] = glm::vec3(-15.0f, 2.0f, -15.0f);
            pointLightPositions[3] = glm::vec3(-15.0f, 2.0f,  15.0f);

            yPos = 15.0f;
        }
        
        /*
        static void SceneInit(){

            //camera(glm::vec3(0.0f, 3.0f, 3.0f));
            metalCubePath = "../resources/Models/PhysicsCube/PhysicsCube.obj";
            scenarioModelPath = "../resources/Models/PhysicsFloor/PhysicsFloor.obj";
            containerModelPath = "../resources/Models/Container/container.obj";

            metalCube = new Model(metalCubePath);
            scenario  = new Model(scenarioModelPath);
            container = new Model(containerModelPath);

            textures.loadAll();
            pointLightPositions[0]  = glm::vec3( 15.0f, 2.0f,  15.0f);
            //glm::vec3( 0.0f, 0.3f,  -2.0f),
            pointLightPositions[1] = glm::vec3( 15.0f, 2.0f, -15.0f);
            pointLightPositions[2] = glm::vec3(-15.0f, 2.0f, -15.0f);
            pointLightPositions[3] = glm::vec3(-15.0f, 2.0f,  15.0f);

            yPos = 15.0f;
        }
        */

        inline void SceneRender(float deltaTime, float currentFrame, Shader &globalShader){

            // TEXTURE BINDING 
            //textures.woodBoxContainer.bindTexture(1);
            textures.pixelRedEye.bindTexture(7);
            textures.container2.bindTexture(4);
            textures.container2Spec.bindTexture(5);
            textures.container2WoodEmission.bindTexture(6);

            // GLOBAL VIEW & PROJECTION 
            glm::mat4 globalView       = glm::mat4(1.0f);
            glm::mat4 globalProjection = glm::mat4(1.0f);
            globalView = camera->GetViewMatrix(); 
            globalProjection = glm::perspective(glm::radians(camera->Fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
            // LIGHT POS ROTATION 
            globalShader.use();
            globalShader.setFloat("flashLight.cutOff", glm::cos(glm::radians(15.0f)));
            globalShader.setFloat("flashLight.outerCutOff", glm::cos(glm::radians(20.0f)));
            globalShader.setVec3("viewPos", camera->Position);
    

            //d = v * t 
            float velocity = 0.8f;
            float distance = velocity * currentFrame;

            //printf("Distance: %f\n", distance);

            if (yPos >= 1.0f){
                yPos -= distance;
                //yPos -= velocity;
            }
            else{
                yPos += distance;
                //yPos += velocity;
            } 

            globalShader.use();        
            globalShader.setFloat("material.shininess", 256);
            glm::mat4 metalCubeModel = glm::mat4(1.0f);
            metalCubeModel = glm::translate(metalCubeModel, glm::vec3(0.0f, yPos, -10.0f));
            metalCubeModel = glm::scale    (metalCubeModel, glm::vec3(1.0f, 1.0f, 1.0f));
            //metalCubeModel = glm::rotate(metalCubeModel, glm::radians(90.0f + currentFrame * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 metalCubeModelInverse = glm::inverse(metalCubeModel); // NORMAL MATRIX
            unsigned int metalCubeModelLoc    = glGetUniformLocation(globalShader.getShaderID(), "model");
            unsigned int metalCubeModelInvLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse"); 
            unsigned int metalCubeViewLoc     = glGetUniformLocation(globalShader.getShaderID(), "view");
            unsigned int metalCubeProjLoc     = glGetUniformLocation(globalShader.getShaderID(), "projection");
            glUniformMatrix4fv(metalCubeModelLoc   , 1, GL_FALSE, glm::value_ptr(metalCubeModel));
            glUniformMatrix4fv(metalCubeModelInvLoc, 1, GL_FALSE, glm::value_ptr(metalCubeModelInverse));
            glUniformMatrix4fv(metalCubeViewLoc    , 1, GL_FALSE, glm::value_ptr(globalView));
            glUniformMatrix4fv(metalCubeProjLoc    , 1, GL_FALSE, glm::value_ptr(globalProjection));
            metalCube->draw(globalShader);

            globalShader.use();
            globalShader.setFloat("material.shininess", 1);
            glm::mat4 scenarioModel = glm::mat4(1.0f);
            scenarioModel = glm::translate(scenarioModel, glm::vec3(0.0f, 0.0f, 0.0f));
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
            scenario->draw(globalShader);

            /*
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
            */
    
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
                metalCube->draw(globalShader);
            }
            globalShader.setBool("pointLightSource", 0); // RESET VALUE


        }
};

#endif // SCENE_H!
