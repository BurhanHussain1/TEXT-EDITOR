#include "huffMan.h"
#include "consoleDesign.h"

HuffTNode::HuffTNode()
{
	key = '*';
	frequ = 0;
	left = nullptr;
	right = nullptr;
}

HuffTNode* createHuffTNode(char x, int p)
{
	HuffTNode* temp = new HuffTNode;
	temp->key = x;
	temp->frequ = p;
	return temp;
}

HuffLLNode::HuffLLNode()
{
	next = nullptr;
	ptr = nullptr;
}

HuffLL::HuffLL()
{
	head = nullptr;
}

HuffLLNode* HuffLL::createNode(char x, int p)
{
	HuffLLNode* temp = new HuffLLNode;
	temp->ptr = createHuffTNode(x, p);
	return temp;

}

HuffLLNode* HuffLL::createNode(HuffTNode* newNode)
{
	HuffLLNode* temp = new HuffLLNode;
	temp->ptr = newNode;
	return temp;

}

void HuffLL::insert(char x, int p)
{
	if (!head)
	{
		head = createNode(x, p);
		return;
	}
	else if (p <= head->ptr->frequ)								//case: insert at begin
	{
		HuffLLNode* temp = createNode(x, p);
		temp->next = head;
		head = temp;
		return;
	}
	else
	{
		HuffLLNode* curr = head;
		while (curr->next)
		{
			curr = curr->next;
		}
		if (p >= curr->ptr->frequ)								//case: insert at end
		{
			curr->next = createNode(x, p);
			return;
		}
		else													//case: insert in middle
		{
			curr = head;
			while (curr->next)
			{
				if (curr->next->ptr->frequ > p)					//insert here
				{
					HuffLLNode* temp = createNode(x, p);
					temp->next = curr->next;
					curr->next = temp;
					return;
				}
				curr = curr->next;
			}
			return;
		}
	}
}

void HuffLL::insert(HuffTNode* newNode)
{
	if (!head)
	{
		head = createNode(newNode);
		return;
	}
	else if (newNode->frequ <= head->ptr->frequ)					//case: insert at begin
	{
		HuffLLNode* temp = createNode(newNode);
		temp->next = head;
		head = temp;
		return;
	}
	else
	{
		HuffLLNode* curr = head;
		while (curr->next)
		{
			curr = curr->next;
		}
		if (newNode->frequ >= curr->ptr->frequ)						//case: insert at end
		{
			curr->next = createNode(newNode);
			return;
		}
		else														//case: insert in middle
		{
			curr = head;
			while (curr->next)
			{
				if (curr->next->ptr->frequ > newNode->frequ)		//insert here
				{
					HuffLLNode* temp = createNode(newNode);
					temp->next = curr->next;
					curr->next = temp;
					return;
				}
				curr = curr->next;
			}
			return;
		}
	}
}

HuffTNode* HuffLL::get_del()
{
	HuffTNode* temp = head->ptr;
	if (head->next)
		head = head->next;
	else
		head = nullptr;
	return temp;
}

void HuffLL::merge()
{
	HuffLLNode* curr = head;
	int count = 1;
	while (curr->next)
	{
		++count;
		curr = curr->next;
	}
	HuffTNode* node1, * node2, * node3;

	//loop start
	for (int i = 0; i < count - 1; ++i)
	{
		node3 = new HuffTNode;
		node1 = get_del();
		node2 = get_del();
		node3->left = node1;
		node3->right = node2;
		node3->frequ = node1->frequ + node2->frequ;
		insert(node3);
	}	//loop end

}

int* findFreq(std::vector<std::string> text, int freq[26])
{
	std::string word;
	size_t s = 0;
	for (auto i = text.begin(); i < text.end(); ++i)
	{
		word = *i;
		s = word.length();
		for (int j = 0; j < s; ++j)
		{
			++freq[static_cast<int>(word[j]) - 97];
		}
	}
	return freq;
}

HuffLL* genHuffTree(std::vector<std::string> text, bool mode, std::string& fileName)		// true = encode	false = decode
{

	std::fstream encode;
	int freq[26] = { 0 };
	if (mode)								//encode mode
	{
		findFreq(text, freq);
		encode.open(fileName, std::ios::out);
		for (int i = 0; i < 26; ++i)
		{
			encode << freq[i] << ' ';
		}
		encode << '\n';
		encode.close();
	}
	else									//decode mode
	{
		encode.open(fileName, std::ios::in);
		while (!encode)
		{
			clearTypeBox();
			gotoxy(18, 9);
			std::cout << "File not found!";
			gotoxy(15, 10);
			std::cout << "Enter file name again : ";
			std::cin >> fileName;
			encode.open(fileName, std::ios::in);
		}
		for (int i = 0; i < 26; ++i)
			encode >> freq[i];
	}
	HuffLL* LL = new HuffLL;
	for (int i = 0; i < 26; ++i)
	{
		if (freq[i])
		{
			LL->insert(static_cast<char>(i + 97), freq[i]);
		}
	}
	LL->merge();
	//Now we have our first step (creating a LL) done.
	return LL;
}

void getCode(HuffTNode* node, std::string code, char x, std::string& fcode)
{
	if (node->left == NULL && node->right == NULL)
	{
		if (x == node->key)
			fcode = code;
		return;
	}
	else
	{
		getCode(node->left, code + '0', x, fcode);
		getCode(node->right, code + '1', x, fcode);
	}
}

void encode(std::vector<std::string>words, HuffLL* root, std::string fileName)
{
	std::fstream encode;
	encode.open(fileName, std::ios::app);
	size_t s = words.size();
	size_t noc;
	std::string code;
	for (int i = 0; i < s; ++i)
	{
		noc = words[i].length();
		for (int j = 0; j < noc; ++j)
		{
			getCode(root->head->ptr, "", (words[i])[j], code);
			encode << code;
		}
		encode << ' ';
	}
	encode.close();
}

int decode(std::vector<std::string>& words, HuffLL* root, std::string& fileName)
{
	words.clear();
	std::fstream decode;
	decode.open(fileName, std::ios::in);
	std::string temp;
	size_t codeSize = 0;
	std::string word = "";
	int t;

	for (int i = 0; i < 26; ++i)
		decode >> t;
	clearTypeBox();
	clearSuggBox();
	int location = 0;
	HuffTNode* curr = root->head->ptr;
	while (1)
	{
		decode >> temp;
		if (decode.eof())
			break;
		codeSize = temp.length();
		for (int i = 0; i < codeSize; ++i)
		{
			if (temp[i] == '1')
			{
				curr = curr->right;
				if (curr->key != '*')
				{
					gotoxy((location % 52) + 1, (location / 52) + 2);
					std::cout << curr->key;
					word += curr->key;
					curr = root->head->ptr;
					++location;
				}
			}
			else if (temp[i] == '0')
			{
				curr = curr->left;
				if (curr->key != '*')
				{
					gotoxy((location % 52) + 1, (location / 52) + 2);
					std::cout << curr->key;
					word += curr->key;
					curr = root->head->ptr;
					++location;
				}
			}
		}
		std::cout << ' ';
		words.push_back(word);
		word = "";
		++location;
	}
	return location;
}