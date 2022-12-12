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
	while (letter != 27) // 27 is ASCII for escape
	{
		display.PrintHeader(util); // Displays header for user.
		display.PrintUI(util);
		display.PrintLineCount(util, nodeManager);
		util.gotoxy(xCursorOffset + xCursor, yCursorOffset + yCursor);
		letter = _getch();

		if (letter == 0) // Function key
		{
			letter = _getch();
			if (letter == 59) // F1 hit
			{
				util.SaveFile(lines);
			}
			if (letter == 60) // F2 hit
			{
				util.LoadFile(lines, curr, start, nodeManager, xCursor, yCursor);
			}
			if (letter == 61) // F3 hit
			{
				util.ClearFile(lines, curr, start, xCursor, yCursor, nodeManager);
			}
		}

		if (letter == -32) // Special character entered.
		{
			letter = _getch();
			if (letter == 75) // Left pressed 
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
			else if (letter == 77) // Right pressed
			{
				if (curr != nullptr) // Check if curr is pointing to anything.
				{
					if (curr->next != nullptr) // Make sure that right arrow cannot go out of bounds.
					{
						if (xCursor != 0) // Only move to next if we are at cursor zero. Prevents curr from being set incorrectly
						{
							// Move current pointer right one.
							curr = curr->next;
						}

						// Move cursor right
						xCursor++;
					}
				}
			}
			else if (letter == 72) // Up pressed
			{
				if (yCursor != 0) // Don't allow cursor to go above top line.
				{
					if (lines[yCursor - 1] != nullptr) // Is there data one line up?
					{
						yCursor--;
						start = lines[yCursor];
						curr = start;
						int counter = xCursor;
						xCursor = 0;

						if (curr->c != '\0') // This is a blank line with only a blank character.
						{
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
				}
			}
			else if (letter == 80) // Down pressed
			{
				if (yCursor != 9)// Don't allow cursor to go below bottom line.
				{
					if (lines[yCursor + 1] != nullptr) // Is there data one line down?
					{
						yCursor++;
						start = lines[yCursor];
						curr = start;
						int counter = xCursor;
						xCursor = 0;

						if (curr->c != '\0') // This is a blank line with only a blank character.
						{
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
				}
			}
		}
		else if (letter == 13) // Enter pressed
		{
			letter = '\n';
			if (nodeManager.lineCount < 10)
			{
				nodeManager.AddNode(&curr, &start, lines, xCursor, yCursor, letter);
			}
		}
		else if (letter == 27)
		{
			// Do nothing. Prevents ecape key from being processed into linked list.
		}
		else if (letter == 59)
		{
			// Do nothing. Prevents f1 key from being processed into linked list.
		}
		else if (letter == 60)
		{
			// Do nothing. Prevents f2 key from being processed into linked list.
		}
		else if (letter == 61)
		{
			// Do nothing. Prevents f3 key from being processed into linked list.
		}

		else if (letter == 8) // BACKSPACE LOGIC
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
