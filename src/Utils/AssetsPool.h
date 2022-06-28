#pragma once
#include<unordered_map>

#include"../Shadering/Shader.h"
#include"../Shadering/Texture.h"

//TODO: MAKE THE SAME THING FOR TEXTURES
class AssetsPool {
private:
	AssetsPool() {};
	static AssetsPool _instance;

	unsigned int gameObjectIndex = 0;
	std::unordered_map<std::string, Shader> shaders;
	std::unordered_map<std::string, Texture> textures;

public:
	 AssetsPool(const AssetsPool&) = delete;

	static AssetsPool& Get() {
		return _instance;
	}

	Shader GetShader(const std::string& filepath);
	unsigned int GetGameObjectID() { return gameObjectIndex++; }

	Texture GetTexture(const std::string& filepath);
	Texture GetTexture(const std::string& filepath, unsigned int index);

};
