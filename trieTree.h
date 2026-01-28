#pragma once
#include <iostream>
#include<conio.h>
#include <Windows.h>
#include <fstream>
#include <vector>

struct TTNode {
	char key;
	TTNode* characters[26];				//26 characcters;
	bool isComplete;
};

class Trie {

	TTNode* root;
public:
	TTNode* getRoot();
	Trie();
	TTNode* createNode();
	bool loadToTree();		//the main function to load the array to tree

};

std::string cStrToStr(char*, int);
void loadSuggestions(std::vector<std::string>&, TTNode*, char*, int);
std::vector<std::string> getSuggestions(std::string, Trie&);