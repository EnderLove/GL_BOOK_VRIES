 
        //// CUBES ROTATING
        //globalShader.use();
        //globalShader.setFloat("material.shininess", 256);
        //globalShader.setInt("material.texture_diffuse1" , 4);
        //globalShader.setInt("material.texture_specular1", 5);
        //globalShader.setInt("material.emission", 6);

        //float texMoveSpeed;
        //globalShader.setFloat("time", glfwGetTime());
        ////globalShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 1.0f));
        ////globalShader.setVec3("lightColor" , glm::vec3(1.0f, 1.0f, 1.0f));

        //glm::mat4 cubeModel = glm::mat4(1.0f);
        //unsigned int modelLoc    = glGetUniformLocation(globalShader.getShaderID(), "model");
        //unsigned int modelInvLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse"); // TODO SET INVERSE FOR ALL MODELS
        //unsigned int viewLoc     = glGetUniformLocation(globalShader.getShaderID(), "view");
        //unsigned int projLoc     = glGetUniformLocation(globalShader.getShaderID(), "projection");
        //glUniformMatrix4fv(viewLoc , 1, GL_FALSE, glm::value_ptr(globalView));
        //glUniformMatrix4fv(projLoc , 1, GL_FALSE, glm::value_ptr(globalProjection));
      
        //glBindVertexArray(VAO[0]);
        //for (unsigned int i = 0; i < 10; i++){
        //    cubeModel = glm::mat4(1.0f);
        //    cubeModel = glm::translate(cubeModel, cubePosition[i]);
        //    cubeModel = glm::scale(cubeModel, glm::vec3(0.7f, 0.7f, 0.7f));
        //    float angle = 20.0f * i;
        //    cubeModel = glm::rotate(cubeModel, glm::radians(angle + currentFrame * 15), glm::vec3(1.0f, 0.3f, 0.5f));

        //    glm::mat4 cubeModelInverse = glm::inverse(cubeModel); // NORMAL MATRIX
        //    glUniformMatrix4fv(modelInvLoc, 1, GL_FALSE, glm::value_ptr(cubeModelInverse));
        //    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));
        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //}

        //SCENARIO FLOOR
        //globalShader.use();
        //globalShader.setInt("material.texture_diffuse1", 2);
        //globalShader.setInt("material.texture_specular1", 2);
        //globalShader.setFloat("material.shininess", 16); 

        //glm::mat4 floorModel= glm::mat4(1.0f);
        //floorModel = glm::translate(floorModel, glm::vec3(0.0f, -2.8f, 0.0f));
        //glm::mat4 floorModelInv = glm::inverse(floorModel);

        //unsigned int floorModelLoc = glGetUniformLocation(globalShader.getShaderID(), "model");
        //unsigned int floorViewLoc  = glGetUniformLocation(globalShader.getShaderID(), "view");
        //unsigned int floorProjLoc  = glGetUniformLocation(globalShader.getShaderID(), "projection");
        //unsigned int floorInvModelLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse"); 
        //glUniformMatrix4fv(floorModelLoc, 1, GL_FALSE, glm::value_ptr(floorModel));
        //glUniformMatrix4fv(floorViewLoc , 1, GL_FALSE, glm::value_ptr(globalView));
        //glUniformMatrix4fv(floorProjLoc , 1, GL_FALSE, glm::value_ptr(globalProjection));
        //glUniformMatrix4fv(floorInvModelLoc, 1, GL_FALSE, glm::value_ptr(floorModelInv));
        //
        //glBindVertexArray(floorVAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //// SCENARIO WALLS
        //globalShader.use();
        //globalShader.setInt("material.texture_diffuse1", 2);
        //globalShader.setInt("material.texture.specular1", 2);

        //for (int i = 0; i < 4; i++){
        //    glm::mat4 wallModel= glm::mat4(1.0f);
        //    wallModel= glm::rotate(wallModel, glm::radians(i * 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //    wallModel= glm::translate(wallModel, glm::vec3(0.0f, -2.8f, -20.0f));
        //    glm::mat4 wallInvModel = glm::inverse(wallModel);
        //    unsigned int wallInvModelLoc = glGetUniformLocation(globalShader.getShaderID(), "modelInverse");
        //    unsigned int wallModelLoc = glGetUniformLocation(globalShader.getShaderID(), "model");
        //    unsigned int wallViewLoc  = glGetUniformLocation(globalShader.getShaderID(), "view");
        //    unsigned int wallProjLoc  = glGetUniformLocation(globalShader.getShaderID(), "projection");
        //    glUniformMatrix4fv(wallInvModelLoc, 1, GL_FALSE, glm::value_ptr(wallInvModel));
        //    glUniformMatrix4fv(wallModelLoc, 1, GL_FALSE, glm::value_ptr(wallModel));
        //    glUniformMatrix4fv(wallViewLoc , 1, GL_FALSE, glm::value_ptr(globalView));
        //    glUniformMatrix4fv(wallProjLoc , 1, GL_FALSE, glm::value_ptr(globalProjection));

        //    glBindVertexArray(wallVAO);
        //    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //}

