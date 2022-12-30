#pragma once
#include "Node.h"
#include <iostream>
#include "Util.h"
#include <Windows.h>

using namespace std;

class Display 
{
private:
	const int COLOR_WHITE = 7;
	const int COLOR_GREEN = 10;
public:
	const static int MAX_LINES = 16;
	void PrintScreen(Node* lines[], Util util, int xCursorOffset, int yCursorOffset);
	void PrintHeader(Util util);
	void PrintUI(Util util);
	void ClearScreen();
};