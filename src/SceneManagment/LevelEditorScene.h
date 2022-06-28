#pragma once
#include"Scene.h"
#include"../Utils/AssetsPool.h"

class LevelEditorScene : public Scene {
private:
public:
	float r = 0.5f;

	LevelEditorScene();

	void OnUpdate(float deltaTime) override;
	void AddGameObjectToScene(GameObject* go) override;
};