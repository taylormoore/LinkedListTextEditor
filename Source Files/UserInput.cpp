#include "UserInput.h"

UserInput::UserInput() 
{
	letter = ' ';
	xCursor = yCursor = 0;
	xCursorOffset = 45;
	yCursorOffset = 5;
}

void UserInput::GetUserInput(Display display, Util util, Node* lines[], Node* curr, Node* start, NodeManager nodeManager) 
{
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
				if (curr != start) 
				{
					xCursor--;
					curr = curr->prev;
				} 
				else 
				{
					if (xCursor == 1) { xCursor -= 1; }
				}
			} 
			else if (letter == RIGHT_ARROW) 
			{
				// Check if curr is pointing to anything.
				if (curr == nullptr || curr->next == nullptr) { continue; }

				// Only move to next if we are at cursor zero. Prevents curr from being set incorrectly
				if (xCursor != 0) { curr = curr->next; }

				// Move cursor right
				xCursor++;
			} 
			else if (letter == UP_ARROW) 
			{
				// Don't allow cursor to go above top line.
				if (yCursor == MIN_ROW_INDEX || lines[yCursor - 1] == nullptr || curr->c == '\0') { continue; }

				yCursor--;
				start = lines[yCursor];
				curr = start;
				int counter = xCursor;
				xCursor = 0;

				// Move current over to where x cursor is.
				for (int i = 0; i < counter - 1; i++) 
				{
					if (curr->next != nullptr) 
					{
						curr = curr->next;
						xCursor++; // Increment x cursor each time we're shifting curr over.
					}
				}

				// Increment one last time to put x cursor at the end of the line.
				if (counter != 0) { xCursor++; }
					
			} 
			else if (letter == DOWN_ARROW) 
			{
				// Don't allow cursor to go below bottom line.
				if (yCursor == MAX_ROW_INDEX || lines[yCursor + 1] == nullptr || curr->c == '\0') { continue; }

				yCursor++;
				start = lines[yCursor];
				curr = start;
				int counter = xCursor;
				xCursor = 0;

				// Move current over to where x cursor is
				for (int i = 0; i < counter - 1; i++) 
				{
					if (curr->next != nullptr) 
					{
						curr = curr->next;
						xCursor++; // Increment x cursor each time we're shifting curr over.
					}
				}

				// Increment one last time to put x cursor at the end of the line. 
				if (counter != 0) { xCursor++; }	
			}
		} 
		else if (letter == ENTER_KEY) 
		{
			if (nodeManager.lineCount < 10) { nodeManager.AddNode(&curr, &start, lines, xCursor, yCursor, '\n'); }
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
