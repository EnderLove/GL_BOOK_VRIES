 
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

