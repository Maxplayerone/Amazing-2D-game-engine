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

		m_Sprite = new Sprite(nullptr);
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

		//we don't actually need m_sprite but I might need it for debugging in the future so think of a better thing than this
		m_Sprite = nullptr;
		m_TextureIndex = texIndex;
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
};
