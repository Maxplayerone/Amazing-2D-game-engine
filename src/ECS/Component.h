#pragma once
#include"../yoinked libs/imGui/imgui.h"
#include"../yoinked libs/imGui/imgui_impl_glfw.h"
#include"../yoinked libs/imGui/imgui_impl_opengl3.h"

class Component {
public:

	void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void ImGui() {};
};