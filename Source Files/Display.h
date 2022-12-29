#pragma once
#include "Node.h"
#include <iostream>
#include "Util.h"
#include <Windows.h>

using namespace std;

class Display 
{
private:
	const int MAX_LINES   = 16;
	const int COLOR_WHITE = 7;
	const int COLOR_GREEN = 10;
public:
	void PrintScreen(Node* lines[], Util util, int xCursorOffset, int yCursorOffset);
	void PrintHeader(Util util);
	void PrintUI(Util util);
	void ClearScreen();
};