#ifndef ICE_GRAPHICS_MODEL_H
#define ICE_GRAPHICS_MODEL_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <Ice\Common\OpenGL.hpp>
#include <Ice\Common\Assimp.hpp>
#include <Ice\Maths\Maths.hpp>
#include <Ice\Graphics\Shader.hpp>
#include <Ice\Graphics\Vertex.hpp>
#include <Ice\Graphics\Mesh.hpp>
#include <Ice\Graphics\Texture.hpp>


using namespace Ice;

class Model
{
public:
	void loadModel(std::string path);

	void Draw(Shader shader);

private:
	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
	std::string directory;

	int loadModelTexture(const char* filename, TextureType type);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType type);
};

#endif	// ICE_GRAPHICS_MODEL_H