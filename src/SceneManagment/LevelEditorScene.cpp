#include"LevelEditorScene.h"

Scene::LevelEditorScene::LevelEditorScene() {
	std::cout << "Entered level editor scene" << std::endl;
}

void Scene::LevelEditorScene::OnUpdate(float deltaTime, float& r) {
	r -= 0.005f;
}