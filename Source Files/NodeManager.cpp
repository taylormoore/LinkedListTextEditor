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
	else if ((*start)->c == '\0') // Inserting a character on a blank line
	{
		delete(*start);

		Node* newNode = CreateNewNode(letter);
		*start = newNode;

		(*start)->prev = nullptr;
		*curr = newNode;
		lines[yCursor] = *start;
	} 
	else if (lines[yCursor] == *start && xCursor == 0) // Inserting at the beginning of a line
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
		// User is inserting a new character at the end of the line
		if ((*curr)->next == nullptr)
		{ 
			// Create node.
			Node* newNode = CreateNewNode(letter);

			// Point current to the new character and make the new character
			// point back to the end of the line
			(*curr)->next = newNode;
			newNode->prev = *curr;

			// Move current to be the new end of the line that was inserted
			*curr = (*curr)->next;
		} 
		// User is inserting a new character in the middle of the line
		else if ((*curr)->next != nullptr && xCursor != 0) 
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

	xCursor += 1;
}

void NodeManager::RemoveNode(Node** curr, Node** start, Node* lines[], int &xCursor, int &yCursor) 
{
	// Do nothing is curr is null
	if (*curr == nullptr) { return; }

	// User is deleting the first character of the line
	if (*curr == *start) 
	{
		// There is only one character on the line
		if ((*start)->next == nullptr) 
		{
			// Do nothing if this is a blank line from the enter key
			if ((*start)->c == '\0') { return; } 

			// Delete the character and reset all pointers
			delete(*start);
			*start = nullptr;
			*curr = nullptr;
			lines[yCursor] = this->CreateNewNode('\0');
		}

		// User is deleting the first character of the line but there are more characters after it
		else if (xCursor > 0) 
		{
			// Set all pointers to the second character in the line
			// then delete the previous character's pointer
			*start = (*curr)->next;
			lines[yCursor] = *start;
			*curr = *start;
			delete((*start)->prev);
			(*start)->prev = nullptr;
		}
	}
	// User is deleting the last character of a line
	else if ((*curr)->next == nullptr) 
	{
		// Move current back one.
		*curr = (*curr)->prev;

		// Delete character that current is pointing to.
		delete((*curr)->next);

		// Make end of current null.
		(*curr)->next = nullptr;
	}
	// User is deleting a character in the middle of the line
	// that is not the first character
	else if ((*curr)->next != nullptr && (*curr)->prev != nullptr) 
	{
		// Move current back one.
		*curr = (*curr)->prev;

		// Link curr->next to two spaces ahead
		(*curr)->next = (*curr)->next->next;

		// delete character in the middle
		delete((*curr)->next->prev);

		// Link character ahead back to curr.
		(*curr)->next->prev = *curr;
	}

	// Move cursor back one. Performed for all cases except for when 
	// the xCursor is all the way to the left
	if (xCursor > 0) { xCursor -= 1; }
}