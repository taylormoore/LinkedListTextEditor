#include "Display.h"

void Display::PrintScreen(Node* lines[], Util util, int xCursorOffset, int yCursorOffset) {
	// Print the linked list.
	util.gotoxy(20, 20);
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // White
	util.gotoxy(45, 0);

	for (int i = 0; i < 10; i++) {
		if (lines[i] != nullptr) { // Is there data on this line
			Node* p;
			p = lines[i];  // Begin at start for each line.
			while (p != nullptr) {
				util.gotoxy(xCursorOffset, yCursorOffset);
				cout << p->c;
				p = p->next;
				xCursorOffset++;
			}

			yCursorOffset++;
			xCursorOffset = 45;
			cout << endl;
		}
	}

	PrintUI(util);
}

void Display::PrintHeader(Util util) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green
	util.gotoxy(45, 0);
	cout << "Welcome to Taylor's Text Editor";
	util.gotoxy(45, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // White
	cout << "===============================";
}

void Display::PrintUI(Util util) {
	util.gotoxy(45, 18);
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // White
	cout << "===============================";
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green
	util.gotoxy(45, 20);
	cout << "F1 - Save file (Saves to C:\\Temp\\TextEditorSaveFile.txt)";
	util.gotoxy(45, 22);
	cout << "F2 - Load file";
	util.gotoxy(45, 24);
	cout << "F3 - Clear text";
	util.gotoxy(45, 26);
	cout << "ESC - Exit Program";
}

void Display::PrintLineCount(Util util, NodeManager nodeManager) {
	util.gotoxy(39, 3);
	cout << "Lines";

	for (int i = 0; i < 10; i++) {
		util.gotoxy(40, 4 + (i+ 1));
		cout.width(3);
		cout << right << i + 1 << "|";
	}
}

void Display::ClearScreen() {
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
