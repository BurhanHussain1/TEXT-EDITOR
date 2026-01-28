#include "trieTree.h"
#include "consoleDesign.h"

int main()
{
	Trie notepad;
	notepad.loadToTree();				//create tree
	startTyping(notepad);
}