#pragma once
#include"Scene.h"

namespace Scene {
	class LevelEditorScene : public Scene{

		LevelEditorScene();
		void OnUpdate(float deltaTime, float& r) override;
	};
}