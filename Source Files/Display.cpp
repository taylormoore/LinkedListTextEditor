#include "Display.h"

void Display::PrintScreen(Node* lines[], Util util, int xCursorOffset, int yCursorOffset) 
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);
	util.gotoxy(xCursorOffset, yCursorOffset);

	for (int i = 0; i < MAX_LINES; i++) 
	{
		if (lines[i] == nullptr) { continue; } // Skip lines with no data

		Node* p;
		p = lines[i];  // Begin at start for each line.
		while (p != nullptr) 
		{
			util.gotoxy(xCursorOffset, yCursorOffset);
			cout << p->c;
			p = p->next;
			xCursorOffset++;
		}

		yCursorOffset++;
		xCursorOffset = 45;
		cout << endl;
	}

	PrintUI(util);
}

void Display::PrintHeader(Util util) 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_GREEN);
	util.gotoxy(45, 0);
	cout << "Taylor's Text Editor";
	util.gotoxy(45, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);
	cout << "===============================";
}

void Display::PrintUI(Util util) 
{
	util.gotoxy(45, 18);
	cout << "===============================";
	util.gotoxy(45, 20);
	cout << "F1 - Save file (Saves to C:\\Temp\\TextEditorSaveFile.txt)";
	util.gotoxy(45, 22);
	cout << "F2 - Load file";
	util.gotoxy(45, 24);
	cout << "F3 - Clear text";
	util.gotoxy(45, 26);
	cout << "ESC - Exit Program";
}

void Display::ClearScreen() 
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
