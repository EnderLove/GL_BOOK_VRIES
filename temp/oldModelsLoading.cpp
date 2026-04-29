/*
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
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

        /* 
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
        */

