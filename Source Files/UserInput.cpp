#include "UserInput.h"
#include "Display.h"

UserInput::UserInput() 
{
	letter = ' ';
	xCursor = yCursor = 0;
	xCursorOffset = 45;
	yCursorOffset = 2;
}

void UserInput::GetUserInput(Display display, Util util, Node* lines[], Node* curr, Node* start, NodeManager nodeManager) 
{
	// The program exits when the user hits the escape key
	while (letter != ESCAPE_KEY) 
	{
		// Display user interface
		display.PrintHeader(util); 
		display.PrintUI(util);

		// Place cursor in correct location
		util.gotoxy(xCursorOffset + xCursor, yCursorOffset + yCursor);

		// Poll for user input from keyboard
		letter = _getch();

		// Check if function key or special character has been pressed
		if (letter == F_KEY_INIT || letter == SPEC_CHAR) 
		{
			// For special characters, input must be polled again to retrieve 
			// the specific special character that has been pressed
			letter = _getch();

			if (letter == F1_KEY) { util.SaveFile(lines); }
			
			if (letter == F2_KEY) { util.LoadFile(lines, curr, start, nodeManager, xCursor, yCursor); }
			
			if (letter == F3_KEY) { util.ClearFile(lines, curr, start, xCursor, yCursor, nodeManager); }
			
			if (letter == LEFT_ARROW) 
			{
				// If we are at the start of the line but our cursor is on the right side of the character
				if (curr == start && xCursor == 1)
				{
					xCursor -= 1;
					continue;
				}
				
				// If we aren't at the beginning of our line,
				// move our curr pointer and update xCursor
				if (curr->prev != nullptr)
				{
					xCursor -= 1;
					curr = curr->prev;
				}
			} 
			else if (letter == RIGHT_ARROW)
			{
				// Prevents the cursor from going out of bounds
				if (curr->next == nullptr) { continue; }

				// Only move to next if we are at cursor zero. Prevents curr from being set incorrectly
				if (xCursor != 0) 
				{
					curr = curr->next;
				}

				xCursor++;
			}
			else if (letter == UP_ARROW) 
			{
				// Don't allow cursor to go above top line.
				if (yCursor <= MIN_ROW_INDEX || lines[yCursor - 1] == nullptr) { continue; }
				
				// After changing yCursor position, reset our start and curr pointers and
				// then place curr where it needs to go based on xCursor position
				yCursor--;
				start = lines[yCursor];
				curr = start;
				MoveCurrentToXCursor(xCursor, xCursor, curr, start);
			} 
			else if (letter == DOWN_ARROW) 
			{
				// Don't allow cursor to go below bottom line.
				if (yCursor >= MAX_ROW_INDEX || lines[yCursor + 1] == nullptr) { continue; }
				
				// After changing yCursor position, reset our start and curr pointers and
				// then place curr where it needs to go based on xCursor position
				yCursor++;
				start = lines[yCursor];
				curr = start;
				MoveCurrentToXCursor(xCursor, xCursor, curr, start);
			}
		} 
		else if (letter == ENTER_KEY) 
		{
			if (nodeManager.lineCount < Display::MAX_LINES) { nodeManager.AddNode(&curr, &start, lines, xCursor, yCursor, '\n'); }
		} 
		else if (letter == BACKSPACE_KEY) 
		{
			nodeManager.RemoveNode(&curr, &start, lines, xCursor, yCursor);
		} 
		else 
		{
			nodeManager.AddNode(&curr, &start, lines, xCursor, yCursor, letter);
		}

		// Print the linked list.
		display.PrintScreen(lines, util, xCursorOffset, yCursorOffset);
	}
}

void UserInput::MoveCurrentToXCursor(int xTarget, int& xCursor, Node*& curr, Node* start)
{
	int counter = xCursor;
	xCursor = 0;

	// Do nothing if the line we've arrowed to is blank
	if (curr->c == '\0') { return; }
	
	// Move current over to where x cursor is.
	for (int i = 0; i < counter - 1; i++) 
	{
		if (curr->next != nullptr)
		{
			curr = curr->next;
			xCursor++; 
		}
	}

	// Increment one last time to put x cursor at the end of the line. 
	if (counter != 0)
	{
		xCursor++; 
	}
}
