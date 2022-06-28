#include"LevelScene.h"

LevelScene::LevelScene() {
	this->m_renderer = new Renderer();
}

void LevelScene::OnUpdate(float deltaTime) {
	m_renderer->ChangeBGColor(0.44f, 0.47f, 0.97f, 1.0f);
}