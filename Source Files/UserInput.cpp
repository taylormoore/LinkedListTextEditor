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
		display.PrintLineCount(util, nodeManager);

		// Place cursor in correct location
		util.gotoxy(xCursorOffset + xCursor, yCursorOffset + yCursor);

		// Poll for user input from keyboard
		letter = _getch();

		// Function keys. Used for Save, Load, and Clear functions.
		if (letter == F_KEY_INIT) 
		{
			letter = _getch();
			if (letter == F1_KEY) 
			{
				util.SaveFile(lines);
			}
			if (letter == F2_KEY) 
			{
				util.LoadFile(lines, curr, start, nodeManager, xCursor, yCursor);
			}
			if (letter == F3_KEY) 
			{
				util.ClearFile(lines, curr, start, xCursor, yCursor, nodeManager);
			}
		}

		else if (letter == SPEC_CHAR) // Special character entered.
		{
			letter = _getch();

			if (letter == LEFT_ARROW)
			{
				if (curr != start)
				{
					xCursor--;
					curr = curr->prev;
				}
				else
				{
					if (xCursor == 1)
					{
						xCursor--;
					}
				}
			}
			else if (letter == RIGHT_ARROW) // Right pressed
			{
				// Check if curr is pointing to anything.
				if (curr == nullptr)
					continue;

				if (curr->next == nullptr)
					continue;

				if (xCursor != 0) // Only move to next if we are at cursor zero. Prevents curr from being set incorrectly
				{
					// Move current pointer right one.
					curr = curr->next;
				}

				// Move cursor right
				xCursor++;
			}
			else if (letter == UP_ARROW) // Up pressed
			{
				// Don't allow cursor to go above top line.
				if (yCursor == MIN_ROW_INDEX)
					continue;

				// There is no data on above line. Do nothing.
				if (lines[yCursor - 1] == nullptr)
					continue;

				yCursor--;
				start = lines[yCursor];
				curr = start;
				int counter = xCursor;
				xCursor = 0;

				// This is a blank line with only a blank character. We don't need to alter our xCursor
				if (curr->c == '\0')
					continue;

				for (int i = 0; i < counter - 1; i++) // Move current over to where x cursor is.
				{
					if (curr->next != nullptr)
					{
						curr = curr->next;
						xCursor++; // Increment x cursor each time we're shifting curr over.
					}
				}

				if (counter != 0)
				{
					xCursor++; // Increment one last time to put x cursor at the end of the line. 
				}
			}
			else if (letter == DOWN_ARROW) // Down pressed
			{
				// Don't allow cursor to go below bottom line.
				if (yCursor == MAX_ROW_INDEX)
					continue;

				// There is no data on below line. Do nothing.
				if (lines[yCursor + 1] == nullptr)
					continue;

				yCursor++;
				start = lines[yCursor];
				curr = start;
				int counter = xCursor;
				xCursor = 0;

				// This is a blank line with only a blank character. We don't need to alter our xCursor.
				if (curr->c == '\0')
					continue;

				for (int i = 0; i < counter - 1; i++) // Move current over to where x cursor is.
				{
					if (curr->next != nullptr)
					{
						curr = curr->next;
						xCursor++; // Increment x cursor each time we're shifting curr over.
					}
				}

				if (counter != 0)
				{
					xCursor++; // Increment one last time to put x cursor at the end of the line. 
				}
			}
		}
		else if (letter == ENTER_KEY) 
		{
			letter = '\n';
			if (nodeManager.lineCount < 10)
			{
				nodeManager.AddNode(&curr, &start, lines, xCursor, yCursor, letter);
			}
		}
		else if (letter == BACKSPACE_KEY) 
		{
			nodeManager.RemoveNode(&curr, &start, lines, xCursor, yCursor);
		}
		else // Regular character (numbers, characters, special symbols)
		{
			nodeManager.AddNode(&curr, &start, lines, xCursor, yCursor, letter);
		}

		// Print the linked list.
		display.PrintScreen(lines, util, xCursorOffset, yCursorOffset);
	}
}
