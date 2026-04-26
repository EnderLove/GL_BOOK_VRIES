#ifndef EDIT_MODE_UI_H
#define EDIT_MODE_UI_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "shader.h"

class EditMode{
    private:
        bool cameraFlashlight = false;
    public:
        EditMode(GLFWwindow *window);
        ~EditMode();
        
        void modifyShader(Shader &shader);


};

#endif // !EDIT_MODE_UI_H
