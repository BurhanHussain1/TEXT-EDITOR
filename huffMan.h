#pragma once
#include "trieTree.h"

struct HuffTNode {											//Tree node
	HuffTNode* left, * right;
	char key;
	int frequ;
	HuffTNode();
};

struct HuffLLNode {											//Linkedlist Node
	HuffLLNode* next;
	HuffTNode* ptr;
	HuffLLNode();
};

struct HuffLL {												//Linkedlist
	HuffLLNode* head;

	HuffLL();
	HuffLLNode* createNode(char, int);
	HuffLLNode* createNode(HuffTNode*);				//overloaded insert used while merging
	void insert(char, int);
	void insert(HuffTNode*);						//overloaded insert used while merging
	HuffTNode* get_del();
	void merge();

};

int* findFreq(std::vector<std::string>, int[26]);
HuffLL* genHuffTree(std::vector<std::string>, bool, std::string&);
void getCode(HuffTNode*, std::string, char, std::string&);
void encode(std::vector<std::string>, HuffLL*, std::string);
int decode(std::vector<std::string>&, HuffLL*, std::string&);