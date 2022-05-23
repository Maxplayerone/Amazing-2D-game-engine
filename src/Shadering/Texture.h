#pragma once
#include<iostream>

class Texture {
private:
	unsigned int m_TextureID;
	std::string m_FilePath;
	unsigned char* m_imageBuffer;
	int m_width, m_height, m_channels;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
};
