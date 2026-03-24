#include "load2DTexture.h"

Gen2DTexture::Gen2DTexture(unsigned int &name, unsigned int n){
    glGenTextures(1, &name);
    ID = &name;
    printf("%p || %p\n", ID, &name);
}

void Gen2DTexture::bindTexture(){ glBindTexture(GL_TEXTURE_2D, *ID); }

void Gen2DTexture::texParamter(int wrapS, int wrapT, int minFilter, int magFilter) const{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}
    
void Gen2DTexture::texData(char const *path, int sourceColorType){
    int width, height, nrChannels;
    unsigned char *texBoxData = stbi_load(path, &width, &height, &nrChannels, 0);
    if (texBoxData){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, sourceColorType, GL_UNSIGNED_BYTE, texBoxData);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("FAILED TO LOAD TEXTURE\n");
    }
    stbi_image_free(texBoxData);
}
