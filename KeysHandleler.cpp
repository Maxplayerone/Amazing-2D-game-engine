#include"KeysHandleler.h"

KeyHandleler::KeyHandleler() {
	for (int i = 0; i < ARRAY_LEN; i++)
		keys[i] = false;
}

bool KeyHandleler::IsKeyPressed(int key) {

	if (key < KeyHandleler::Get().Length())
		return keys[key];
	else
		return false;
}