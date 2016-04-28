#ifndef _MODEL_H_
#define _MODEL_H_

#include "Mesh.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <Ice/Graphics/Shader.hpp>
#include <Texture.hpp>

class Model
{
public:
	Model(GLchar* path);
	void Draw(Shader& shader);

private:
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	GLint TextureFromFile(const char* path, std::string directory)
};

#endif