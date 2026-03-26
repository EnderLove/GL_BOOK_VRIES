#define STB_IMAGE_IMPLEMENTATION
#include "load2DTexture.h"

// TEXTURE CREATION ///////////////////////////////////////////////////////////////////////////////////////////
class LoadTextures{
    public:
        Gen2DTexture woodBoxContainer;
        Gen2DTexture smileyYellowFace;
        Gen2DTexture floor;
        Gen2DTexture pixelRedEye;
        Gen2DTexture metal;

        void loadAll(){
            woodBoxContainer.loadTexture("../resources/textures/container.jpg", GL_RGB, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
            pixelRedEye.loadTexture("../resources/textures/pixelArtEye.png", GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
            floor.loadTexture("../resources/textures/wall.jpg", GL_RGB, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
            metal.loadTexture("../resources/textures/wall.jpg", GL_RGB, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
        }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
