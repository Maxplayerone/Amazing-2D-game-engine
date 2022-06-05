#pragma once
#include<iostream>

class Component {
public:
	std::string m_name;

	virtual void Start() {};
	virtual void Update(float deltaTime) {};
};