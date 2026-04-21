#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "stb_image.h"

class Model{
    private:
        std::vector<Texture> textures_loaded;
    public:
        Model(char *path);
        void draw(Shader &shader);

    private:
        // Model data
        std::vector<Mesh> meshes;
        std::string directory;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
       
        unsigned int textureFromFile(const char *path, const std::string directory);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif // !MODEL_H
