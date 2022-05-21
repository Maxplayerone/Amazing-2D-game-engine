#include"LevelScene.h"

Scene::LevelScene::LevelScene() {
	std::cout << "Entered level scene" << std::endl;
}

void Scene::LevelScene::OnUpdate(float deltaTime, float& r) {
	r += 0.005f;
}