#include"KeysHandleler.h"

KeyHandleler::KeyHandleler() {
	for (int i = 0; i < ARRAY_LEN; i++)
		m_keys[i] = false;
}

bool KeyHandleler::IsKeyPressed(int key) {

	//Can't find the key value
	if (!(key < KeyHandleler::Get().Length()))
		return false;

	bool heldKey = m_keys[key];
	m_keys[key] = false;
	return heldKey;
}

bool KeyHandleler::IsKeyHeld(int key) {
	if (key < KeyHandleler::Get().Length())
		return m_keys[key];
	else
		return false;
}