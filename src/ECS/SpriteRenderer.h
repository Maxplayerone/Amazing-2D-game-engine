#pragma once
#include"Component.h"
#include"Sprite.h"

#include<iostream>

#include"../Shadering/Texture.h"

class SpriteRenderer : public Component {
public:
	float r;
	float b;
	float g;
	float a;

	SpriteRenderer(float _r, float _g, float _b, float _a){
		r = _r;
		g = _g;
		b = _b;
		a = _a;

		m_Sprite = GetDummySprite();
		m_TextureIndex = 0;
	}

	SpriteRenderer(Sprite* sprite){
		r = 1.0f;
		b = 1.0f;
		g = 1.0f;
		a = 1.0f;

		m_Sprite = sprite;
		m_TextureIndex = sprite->GetTexSlot();
	}

	SpriteRenderer(unsigned int texIndex) {
		r = 1.0f;
		b = 1.0f;
		g = 1.0f;
		a = 1.0f;


		m_TextureIndex = texIndex;
		m_Sprite = GetDummySprite();
	}

	unsigned int GetTexIndex() const { return m_TextureIndex; }
	float* GetTexCoords() const { return m_Sprite->GetTexCoords(); }
	Texture* GetTexture() const { return m_Sprite->GetTexture(); }


	void Start() override {
		std::cout << "Creating sprite renderer" << std::endl;
	}

	void Update(float deltaTime) override {
		std::cout << "Updating sprite renderer" << std::endl;
	}

private:
	unsigned int m_TextureIndex;
	Sprite* m_Sprite;

	Sprite* GetDummySprite() {
		float texCoords[8] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f
		};
		 return new Sprite(texCoords);
	}
};
