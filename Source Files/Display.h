#pragma once
#include "Node.h"
#include <iostream>
#include "Util.h"
#include <Windows.h>

using namespace std;

class Display {
public:
	void PrintScreen(Node* lines[], Util util, int xCursorOffset, int yCursorOffset);
	void PrintHeader(Util util);
	void PrintUI(Util util);
	void PrintLineCount(Util util, NodeManager nodeManager);
	void ClearScreen();
	
};