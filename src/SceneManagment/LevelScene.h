#pragma once
#include"Scene.h"

namespace Scene {
	class LevelScene : public Scene {
	public:
		LevelScene();
		void OnUpdate(float deltaTime, float& r) override;
	};
}
