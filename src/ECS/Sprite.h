#pragma once
#include"../Shadering/Texture.h"

class Sprite {
private:
	Texture* m_texture;
	float m_TexCoords[8];

public:
	Sprite(Texture* _texture)
	: m_texture(_texture)
	{
		float leftX = 0.0f;
		float rightX = m_texture->GetWidth();
		float topY = m_texture->GetHeight();
		float bottomY = 0.0f;

		float texCoords[8] = {
			leftX, bottomY,
			rightX, bottomY,
			leftX, topY,
			rightX, topY
		};
	}

	Sprite(Texture* _texture, float texCoords[8]) {
		m_texture = _texture;
		for (int i = 0; i < 8; i++) {
			m_TexCoords[i] = texCoords[i];
		}
	}

	Sprite(float texCoords[8]) {
		m_texture = nullptr;
		for (int i = 0; i < 8; i++) {
			m_TexCoords[i] = texCoords[i];
		}
	}

	float* GetTexCoords() { return m_TexCoords; }
	Texture* GetTexture() const { if(m_texture != nullptr) return m_texture; }
	unsigned int GetTexSlot() const { return m_texture->GetSlot(); }
};
