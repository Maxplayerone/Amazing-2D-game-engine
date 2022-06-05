#pragma once
#include"Component.h"
#include<iostream>

class Transform : public Component {
public:
	Transform(std::string name)
		: m_name(name)
	{}

	std::string m_name;

	void Start() override {
		std::cout << "Creating transform object" << std::endl;
	}

	void Update(float deltaTime) override {
		std::cout << "Updating transform object" << std::endl;
	}
};
