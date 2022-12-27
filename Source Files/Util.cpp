#include "Util.h"

void Util::gotoxy(int column, int line) 
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Util::SaveFile(Node* lines[]) 
{
	ofstream myFile("C:\\Temp\\TextEditorSaveFile.txt");
	
	// If opening this file fails, the user likely is missing a temp directory in C drive. Make one for them.
	if (myFile.fail()) 
	{
		CreateDirectoryA("C:\\Temp", NULL);
		ofstream myFile("C:\\Temp\\TextEditorSaveFile.txt");
	}
	
	for (int i = 0; i < 10; i++) 
	{
		// Skip lines that contain no data
		if (lines[i] == nullptr) { continue; }
		
		// Begin at start for each line and print each character in it to the file
		Node* p;
		p = lines[i];  
		while (p != nullptr) 
		{
			if (p->c != '\0') { myFile << p->c; }
			p = p->next;
		}

		if (i < 9 && lines[i + 1] != nullptr) { myFile << endl; }
	}

	myFile.close();
}

void Util::LoadFile(Node* lines[], Node* &curr, Node* &start, NodeManager &nodeManager, int &xCursor, int &yCursor) 
{
	ifstream myFile("C:\\temp\\TextEditorSaveFile.txt");
	string line;
	int charCount = 0;
	nodeManager.lineCount = 1;

	ClearFile(lines, curr, start, xCursor, yCursor, nodeManager);

	while (getline(myFile, line, '\0')) 
	{
		for (char c : line) 
		{
			if (c != '\0') { nodeManager.AddNode(&curr, &start, lines, xCursor, yCursor, c); }
		}
	}
}

void Util::ClearFile(Node* lines[], Node*& curr, Node*& start, int &xCursor, int &yCursor, NodeManager &nodeManager) 
{
	// Clear any data from each line
	for (int i = 0; i < 10; i++) 
	{
		lines[i] = nullptr;
	}
	nodeManager.lineCount = 1;
	curr = start = nullptr;
	xCursor = 0;
	yCursor = 0;
}
