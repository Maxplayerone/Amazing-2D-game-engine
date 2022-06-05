#pragma once
#include"Component.h"
#include<iostream>

class SpriteRenderer : public Component {
public:
	SpriteRenderer(std::string name)
		: m_name(name), value(0)
	{}

	std::string m_name;
	int value;

	void Start() override {
		std::cout << "Creating sprite renderer" << std::endl;
	}

	void Update(float deltaTime) override {
		std::cout << "Updating sprite renderer" << std::endl;
	}
};
