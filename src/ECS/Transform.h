#pragma once
#include"Component.h"
#include<iostream>

class Transform : public Component {
public:
	float x;
	float y;

	Transform(float posX, float posY) {
		x = posX;
		y = posY;
 	}
};
