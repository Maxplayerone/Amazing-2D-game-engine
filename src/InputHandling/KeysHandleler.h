#pragma once

#define ARRAY_LEN 350

class KeyHandleler {
private:
	KeyHandleler();
public:
	KeyHandleler(const KeyHandleler&) = delete;
	~KeyHandleler() { delete[] keys; }

	static KeyHandleler& Get() {
		static KeyHandleler instance;
		return instance;
	}
	bool* keys = new bool[ARRAY_LEN];

	bool IsKeyPressed(int key);
	int Length() { return ARRAY_LEN; }
};
