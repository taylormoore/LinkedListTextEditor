#pragma once
#include "Node.h"
#include <iostream>

using namespace std;

class NodeManager
{
public:
	NodeManager();
	int lineCount;
	Node* CreateNewNode(char newChar);
	void RemoveNode(Node** curr, Node** start, Node* lines[], int &xCursor, int &yCursor);
	void AddNode(Node** curr, Node** start, Node* lines[], int& xCursor, int& yCursor, char letter);
};