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
public:
	UserInput();
	void GetUserInput(Display display, Util util, Node* lines[], Node* curr, Node* start, NodeManager nodeManager);
};
