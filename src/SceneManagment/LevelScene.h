#pragma once
#include"Scene.h"

#include"../Shadering/Renderer.h"

class LevelScene : public Scene {
public:
	LevelScene();
	void OnUpdate(float deltaTime) override;
};
