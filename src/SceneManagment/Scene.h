#pragma once
#include<iostream>

namespace Scene {
	class Scene {
	public:
		Scene() {}

		virtual void OnUpdate(float deltaTime, float&) {};
	};
}
