#include <iostream>
#include "Node.h"
#include "Util.h"
#include "NodeManager.h"
#include "Display.h"
#include "UserInput.h"

using namespace std;

int main()
{
	// Initialization
	Node* lines[10];
	Node* curr = nullptr;
	Node* start = nullptr;
	Util util;
	UserInput userInput;
	NodeManager nodeManager;
	Display display;

	// Initialize line array. 
	for (int i = 0; i < 10; i++)
		lines[i] = nullptr;

	userInput.GetUserInput(display, util, lines, curr, start, nodeManager);
	return 0;
}
