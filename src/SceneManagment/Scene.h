#pragma once
#include<iostream>

//imGui
#include"../yoinked libs/imGui/imgui.h"
#include"../yoinked libs/imGui/imgui_impl_glfw.h"
#include"../yoinked libs/imGui/imgui_impl_opengl3.h"

//shadering
#include"../Shadering/Renderer.h"
#include"../Shadering/Texture.h"

//ecs
#include"../ECS/SpriteRenderer.h"
#include"../ECS/Transform.h"
#include"../ECS/GameObject.h"
#include"../ECS/SpriteSheet.h"

class Scene {
protected:
	Renderer* m_renderer;
	std::vector<GameObject*> m_gameObjects;
public:
	Scene() {};

	virtual void OnUpdate(float deltaTime) {};

	virtual void AddGameObjectToScene(GameObject* go) {};
};
