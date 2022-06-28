#include"LevelEditorScene.h"

LevelEditorScene::LevelEditorScene(){
	this->m_renderer = new Renderer();	

	GameObject* coloredCube = new GameObject();
	coloredCube->AddComponent(new Transform(-0.5f, -0.5f));
	coloredCube->AddComponent(new SpriteRenderer(0.5f, 0.6f, 0.8f, 1.0f));
	AddGameObjectToScene(coloredCube);

	GameObject* anotherCube = new GameObject();
	anotherCube->AddComponent(new Transform(1.0f, 0.0f));
	anotherCube->AddComponent(new SpriteRenderer(0.6f, 0.1f, 0.2f, 1.0f));
	AddGameObjectToScene(anotherCube);
}

void LevelEditorScene::OnUpdate(float deltaTime) {
	this->m_renderer->ChangeBGColor(0.4f, 0.92f, 0.42f, 1.0f);
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->Update(deltaTime);
	}

	this->m_renderer->Render();
}

void LevelEditorScene::AddGameObjectToScene(GameObject* go) {
	auto itr = std::find(this->m_gameObjects.begin(), this->m_gameObjects.end(), go);
	//the game object is already in the vector
	if (itr != this->m_gameObjects.end()) return;
		
	this->m_gameObjects.push_back(go);
	this->m_renderer->Add(m_gameObjects[m_gameObjects.size() - 1]);
}