#ifndef LOAD_2D_TEXTURE_H
#define LOAD_2D_TEXTURE_H

#include <glad/glad.h>
#include <stdio.h>

#include "stb_image.h"

class Gen2DTexture{
    private:
        unsigned int *ID; // Texture ID
    public:
        Gen2DTexture(unsigned int &name, unsigned int n); 
       
        void bindTexture(); // Binds the texture
        void texParamter(int wrapS, int wrapT, int minFilter, int magFilter) const; // Sets parameters for the texture
        void texData(char const *path, int sourceColorType);                        // Sets the data to load the texture
};

#endif // LOAD_2D_TEXTURE_H!
