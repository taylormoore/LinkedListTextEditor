#pragma once
#include "Node.h"
#include <fstream> // for file io
#include <string> // for getline
#include "NodeManager.h"
#include <Windows.h>
using namespace std;

class Util {
public:
	void gotoxy(int column, int line);
	void SaveFile(Node* lines[]);
	void LoadFile(Node* lines[], Node* &curr, Node* &start, NodeManager &nodeManager, int &xCursor, int &yCursor);
	void ClearFile(Node* lines[], Node*& curr, Node*& start, int &xCursor, int &yCursor, NodeManager &nodeManager);
};
