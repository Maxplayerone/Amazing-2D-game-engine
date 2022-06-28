#pragma once
#include"Component.h"

class Transform : public Component {
private:
	bool dirty;
public:
	float x;
	float y;

	Transform(float posX, float posY) {
		dirty = false;
		x = posX;
		y = posY;
 	}

	void Update(float deltaTime) override {
		//std::cout << "Updating transform" << std::endl;
	}

	void SetPosition(float x, float y) {
		this->x = x;
		this->y = y;
		dirty = true;
	}

	bool IsDirty() { return dirty; }
};
