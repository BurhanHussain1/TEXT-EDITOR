#pragma once
#include "trieTree.h"
const int screenWidth = 53;
const int screenHeight = 20;
const int suggBoxWidth = 75;
const int suggBoxHeight = 20;

void gotoxy(int, int);
void Color(int);
void clearTypeBox();
int typeWords(std::vector<std::string>& words);
bool isValid(std::string);
void borders();
void clearSuggBox();
void startTyping(Trie& dictionary);