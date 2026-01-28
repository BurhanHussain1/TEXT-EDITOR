#include "trieTree.h"

std::string cStrToStr(char* str, int n)
{
	std::string temp;
	for (int i = 0; i < n; i++)
	{
		temp += str[i];
	}
	return temp;
}

Trie::Trie()
{
	root = createNode();
}

TTNode* Trie::getRoot()
{
	return root;
}

TTNode* Trie::createNode()
{
	TTNode* temp = new TTNode;
	for (int i = 0; i < 26; ++i)
		temp->characters[i] = nullptr;

	temp->isComplete = false;
	temp->key = '*';
	return temp;
}

bool Trie::loadToTree()
{
	std::fstream input;
	input.open("outfile.txt", std::ios::in);
	std::string tempWord;									//temp string to store each word temporarily
	size_t alphaCount;
	TTNode* currNodePtr;
	while(!input.eof())						//iterating through each word
	{
		input >> tempWord;
		alphaCount = tempWord.length();
		currNodePtr = root;
		for (int j = 0; j < alphaCount; j++)			//iterating through each alphabet and inserting it
		{
			if (currNodePtr->characters[static_cast<int>(tempWord[j]) - 97])
			{
				currNodePtr = currNodePtr->characters[static_cast<int>(tempWord[j]) - 97];
				if (j == alphaCount - 1)				//check if this is the last letter
					currNodePtr->isComplete = true;
			}
			else
			{
				currNodePtr->characters[static_cast<int>(tempWord[j]) - 97] = createNode();
				currNodePtr = currNodePtr->characters[static_cast<int>(tempWord[j]) - 97];
				currNodePtr->key = tempWord[j];
				if (j == alphaCount - 1)				//check if this is the last letter
					currNodePtr->isComplete = true;
			}

		}
	}
	return true;
}

void loadSuggestions(std::vector<std::string>& v, TTNode* root, char* wordArray, int pos = 0)
{
	if (root == NULL)
		return;
	if (root->isComplete)
	{
		v.push_back(cStrToStr(wordArray, pos));
	}
	for (int i = 0; i < 26; i++)
	{
		if (root->characters[i] != NULL)
		{
			wordArray[pos] = root->characters[i]->key;
			loadSuggestions(v, root->characters[i], wordArray, pos + 1);
		}
	}
}

std::vector<std::string> getSuggestions(std::string tempWord, Trie& dictionary)
{
	size_t alphaCount;
	alphaCount = tempWord.length();
	TTNode* currNodePtr = dictionary.getRoot(), * LLOGW = nullptr;		//LLOGW = Last Letter Of Given Word
	char possibleWord[100];
	bool isWord = true;													//to check if such word even exists

	for (int i = 0; i < alphaCount; ++i)								//traversing through the tree to the last alphabet of input word
	{
		currNodePtr = currNodePtr->characters[static_cast<int>(tempWord[i]) - 97];
		if (!currNodePtr)
		{
			isWord = false;
			break;
		}
	}
	LLOGW = currNodePtr;
	std::vector<std::string> suggestedWords;		//vector to store suggestions
	if (isWord)							//check if such word even exists
		loadSuggestions(suggestedWords, LLOGW, possibleWord);
	return suggestedWords;

}
