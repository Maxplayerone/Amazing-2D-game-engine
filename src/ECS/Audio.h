#pragma once
#include"Component.h"

class Audio : public Component {
public:
	Audio(std::string name) 
		: m_name(name)
	{}

	std::string m_name;

	void Start() override {
		std::cout << "Creating audio component" << std::endl;
	}

	void Update(float deltaTime) override {
		std::cout << "Updating audio component" << std::endl;
	}
};