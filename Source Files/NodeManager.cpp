#include "NodeManager.h"

NodeManager::NodeManager() 
{
	lineCount = 1;
}

Node* NodeManager::CreateNewNode(char newChar) 
{
	// Create node and put character in it
	Node* newNode = new Node();
	newNode->c = newChar;

	return newNode;
}

void NodeManager::AddNode(Node** curr, Node** start, Node* lines[], int& xCursor, int& yCursor, char letter) 
{
	// User has hit enter key
	if (letter == '\n') 
	{ 
		if (yCursor == 0 && lines[0] == nullptr) { lines[yCursor] = CreateNewNode('\0'); }
		yCursor++;
		lines[yCursor] = CreateNewNode('\0');
		xCursor = 0;
		*start = lines[yCursor];
		*curr = *start;
		lineCount++;

		return;
	}

	if (*start == nullptr) 
	{ 
		// Create node.
		Node* newNode = CreateNewNode(letter);

		// Make start point to that node.
		*start = newNode;
		lines[yCursor] = *start;

		*curr = *start;
	} 
	else if ((*start)->c == '\0') 
	{
		delete(*start);


		Node* newNode = CreateNewNode(letter);
		*start = newNode;

		(*start)->prev = nullptr;
		*curr = newNode;
		lines[yCursor] = *start;
	} 
	else if (lines[yCursor] == *start && xCursor == 0) // insert at the beginning
	{ 
		Node* newNode = CreateNewNode(letter);

		(*start)->prev = newNode;
		newNode->next = *start;
		*start = newNode;
		*curr = newNode;
		lines[yCursor] = *start;
	} 
	else 
	{
		if ((*curr)->next == nullptr) // inserting at the end
		{ 
			// Create node.
			Node* newNode = CreateNewNode(letter);

			(*curr)->next = newNode;
			newNode->prev = *curr;

			// Move current
			*curr = (*curr)->next;
		} 
		else if ((*curr)->next != nullptr && xCursor != 0) // insert in middle  
		{ 
			// Create node.
			Node* newNode = CreateNewNode(letter);

			newNode->next = (*curr)->next;

			(*curr)->next->prev = newNode;
			(*curr)->next = newNode;
			newNode->prev = *curr;
			*curr = newNode;
		}
	}

	xCursor++;
}

void NodeManager::RemoveNode(Node** curr, Node** start, Node* lines[], int &xCursor, int &yCursor) 
{
	if (*curr != nullptr) // Check that current is pointing to something.
	{ 
		if (*curr == *start) // Check if we are at the beginning.
		{ 
			if ((*start)->next == nullptr) // There is only one character
			{ 
				if ((*start)->c != '\0') // Only perform operation if the one character isn't a blank line node
				{ 
					delete(*start);
					*start = nullptr;
					*curr = nullptr;
					lines[yCursor] = this->CreateNewNode('\0');
					xCursor--;
				} 
				else 
				{
					return;
				}
			} 
			else // There are characters other than start.
			{ 
				if (xCursor == 0) 
				{
					//Do nothing. We are all the way left
				} 
				else if (xCursor == 1) 
				{
					*start = (*curr)->next;
					lines[yCursor] = *start;
					*curr = *start;
					delete((*start)->prev);
					(*start)->prev = nullptr;

					xCursor--;
				}
			}
		} 
		else if ((*curr)->next == nullptr) // Check that we are at the end of the line
		{ 
			// Move current back one.
			*curr = (*curr)->prev;

			// Delete character that current is pointing to.
			delete((*curr)->next);

			// Make end of current null.
			(*curr)->next = nullptr;

			// Move cursor back one
			xCursor--;
		} 
		else if ((*curr)->next != nullptr && (*curr)->prev != nullptr) // Check if we are in middle
		{ 
			// Move current back one.
			*curr = (*curr)->prev;

			// Link curr next to two spaces ahead
			(*curr)->next = (*curr)->next->next;

			// delete character in the middle
			delete((*curr)->next->prev);

			// Link character ahead back to curr.
			(*curr)->next->prev = *curr;

			// Move cursor back one
			xCursor--;
		}
	}
}