#pragma once

#define ARRAY_LEN 350

class KeyHandleler {
private:
	KeyHandleler();
public:
	bool* m_keys = new bool[ARRAY_LEN];
	
	KeyHandleler(const KeyHandleler&) = delete;
	~KeyHandleler() { delete[] m_keys; }

	static KeyHandleler& Get() {
		static KeyHandleler instance;
		return instance;
	}

	//returns ONCE if the key is pressed 
	bool IsKeyPressed(int key);
	//returns true for as long as the key is pressed
	bool IsKeyHeld(int key);
	int Length() { return ARRAY_LEN; }
};
