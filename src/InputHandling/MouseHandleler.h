#pragma once

#define ARRAY_LEN 3
class MouseHandleler {
private:
	MouseHandleler();
public:

	~MouseHandleler() { delete[] mouseButtons; }

	//deletes an exisitng copy of the class if there is one
	MouseHandleler(const MouseHandleler&) = delete;

	static MouseHandleler& Get() {
		static MouseHandleler instance;
		return instance;
	}

	bool* mouseButtons = new bool[ARRAY_LEN];
	double xOffset;
	double yOffset;

	double xPos;
	double yPos;

	int ArrayLength() { return ARRAY_LEN; }
	//check if any mouse button is pressed
	bool IsMouseButtonPressed(int button);
	//saves the input from the scroll callback into class variables
	//x input doesn't really work on my mouse so yeah, only y is important
	void GetScrollInput(double x, double y);

	void ReturnScrollInput(double* x, double* y);
	bool IsScrolling();

	//gets x and y position of the mouse in relation to the screen
	void GetMousePosAbsolute(double x, double y);

};
