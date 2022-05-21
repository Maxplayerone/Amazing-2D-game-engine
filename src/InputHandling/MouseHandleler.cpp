#include"MouseHandleler.h"
#include<iostream>

MouseHandleler::MouseHandleler() {
	for (int i = 0; i < ARRAY_LEN; i++)
		mouseButtons[i] = false;
}

bool MouseHandleler::IsMouseButtonPressed(int button) {
	if (button > MouseHandleler::Get().ArrayLength()) return false;

	return MouseHandleler::Get().mouseButtons[button];
}

void MouseHandleler::GetScrollInput(double x, double y) {
	if (x != 0)
		MouseHandleler::Get().xOffset = x;
	if (y != 0)
		MouseHandleler::Get().yOffset = y;
}

void MouseHandleler::GetMousePosAbsolute(double x, double y) {
	MouseHandleler::Get().xPos = x;
	MouseHandleler::Get().yPos = y;
}

void MouseHandleler::ReturnScrollInput(double* x, double* y) {
	if (x != 0)
		*x = MouseHandleler::Get().xOffset;
	if (y != 0)
		*y = MouseHandleler::Get().yOffset;
}
