#include"AssetsPool.h"

AssetsPool AssetsPool::_instance;

Shader AssetsPool::GetShader(const std::string& filepath) {
	auto itr = shaders.find(filepath);
	if (itr != shaders.end()) return itr->second;

	Shader tempShader(filepath);
	shaders.insert(std::make_pair(filepath, tempShader));
	return tempShader;
}

Texture AssetsPool::GetTexture(const std::string& filepath) {
	auto itr = textures.find(filepath);
	if (itr != textures.end()) return itr->second;

	Texture tempTex(filepath);
	textures.insert(std::make_pair(filepath, tempTex));
	return tempTex;
}

Texture AssetsPool::GetTexture(const std::string& filepath, unsigned int index) {
	auto itr = textures.find(filepath);
	if (itr != textures.end()) return itr->second;

	Texture tempTex(filepath, index);
	textures.insert(std::make_pair(filepath, tempTex));
	return tempTex;
}