#pragma once
#include <conio.h>
#include "Display.h"
#include "Util.h"

class UserInput
{
private:
	char letter;
	int xCursor, yCursor;
	int xCursorOffset, yCursorOffset;

	const int MAX_ROW_INDEX = 9;
	const int MIN_ROW_INDEX = 0;
	
	// KEY CONSTANTS
	const int ESCAPE_KEY = 27;
	const int F_KEY_INIT = 0;
	const int F1_KEY = 59;
	const int F2_KEY = 60;
	const int F3_KEY = 61;
	const int SPEC_CHAR = -32;
	const int LEFT_ARROW = 75;
	const int RIGHT_ARROW = 77;
	const int UP_ARROW = 72;
	const int DOWN_ARROW = 80;
	const int ENTER_KEY = 13;
	const int BACKSPACE_KEY = 8;

public:
	UserInput();
	void GetUserInput(Display display, Util util, Node* lines[], Node* curr, Node* start, NodeManager nodeManager);
};
