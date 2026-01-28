#include "consoleDesign.h"
#include "huffMan.h"

void gotoxy(int x, int y)   //function to move cursor on console
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Color(int color)		//function to change text colour on console
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearTypeBox()
{
	for (int i = 0; i < 17; ++i)
	{
		gotoxy(1, i + 2);
		for (int j = 0; j < 52; ++j)
		{
			std::cout << ' ';
		}
	}
}

int typeWords(std::vector<std::string>& words)
{
	int location = 0;
	size_t s = words.size();
	size_t wordSize;
	for (int i = 0; i < s; ++i)
	{
		wordSize = words[i].length();
		for (int j = 0; j < wordSize; ++j)
		{
			gotoxy((location % 52) + 1, (location / 52) + 2);
			std::cout << (words[i])[j];
			++location;
		}
		gotoxy((location % 52) + 1, (location / 52) + 2);
		std::cout << ' ';
		++location;
	}
	return location;
}

bool isValid(std::string toCheck)
{
	bool result = true;
	size_t length;
	length = toCheck.length();
	for (int j = 0; j < length; ++j)
	{
		if (toCheck[j] < 97 || toCheck[j] > 122)
		{
			result = false;
			break;
		}
	}
	return result;
}

void borders()
{
	gotoxy(0, 0);
	for (int i = 0; i < suggBoxWidth; ++i)
		std::cout << '=';
	gotoxy(0, screenHeight - 1);
	for (int i = 0; i < suggBoxWidth; ++i)
		std::cout << '=';
	for (int i = 0; i < screenHeight; ++i)
	{
		gotoxy(0, i);
		std::cout << "|";
		if (i != screenHeight - 1)
		{
			gotoxy(screenWidth, i);
			std::cout << "|";
		}
		gotoxy(suggBoxWidth, i);
		std::cout << "|";
	}
	gotoxy(1, 1);
	for (int i = 0; i < 22; ++i)
		std::cout << '_';
	std::cout << " NotePad ";
	for (int i = 0; i < 21; ++i)
		std::cout << '_';
	gotoxy(54, 1);
	for (int i = 0; i < 4; ++i)
		std::cout << '_';
	std::cout << " Suggestions ";
	for (int i = 0; i < 4; ++i)
		std::cout << '_';
	gotoxy(1, screenHeight + 2);
	std::cout << "'/' Next selection     ';' Select     '=' Save     '-' Read     'esc' exit";

	gotoxy(1, 2);
}

void clearSuggBox()
{
	int row = 2;
	for (int j = 0; j <= 16; ++j)
	{
		gotoxy(54, row);
		for (int i = 54; i <= 74; ++i)
			std::cout << ' ';
		++row;
	}
}

void startTyping(Trie& dictionary)
{
	borders();
	char input;
	int location = 0;
	int selected = 0;
	size_t NOfSugg = 0;
	int j = 0;
	std::string word = "";
	std::string temp;
	std::string fileName;
	std::vector<std::string> words;
	std::vector<std::string> suggestions;
	size_t t = 0;
	while (1)
	{
		input = _getch();
		if ((input >= 97 && input <= 122) || input == '/' || input == ';' || input == '=' || input == ' ' || input == '-' || input == 27 || input == '+')
			switch (input)
			{
			case'/':		//next option
			{
				if (selected < NOfSugg - 1)
					++selected;
				else
					selected = 0;
				j = 3;
				for (auto i = suggestions.begin(); i < suggestions.end() && j < 13; ++i)
				{
					if ((j - 3) == selected)
						Color(1);
					else
						Color(7);
					gotoxy(57, j);
					std::cout << word << *i;
					++j;
				}
				Color(7);
				break;
			}
			case';':		//select
			{
				if (NOfSugg != 0)
				{
					temp = suggestions[selected];
					for (int i = 0; i < temp.length(); ++i)
					{
						gotoxy((location % 52) + 1, (location / 52) + 2);
						std::cout << temp[i];
						word += temp[i];
						++location;
					}
					std::cout << ' ';
					++location;
					words.push_back(word);
					word = "";
					clearSuggBox();
					selected = 0;
				}
				break;
			}
			case'=':		//save
			{
				words.push_back(word);

				clearTypeBox();
				clearSuggBox();
				gotoxy(15, 9);
				std::cout << "Enter file name: ";
				std::cin >> fileName;
				clearTypeBox();
				encode(words, genHuffTree(words, true, fileName), fileName);
				gotoxy(25, 9);
				std::cout << "Saved!";
				Sleep(2000);
				clearTypeBox();
				words.clear();
				word = "";
				location = 0;
				break;
			}
			case'-':		//retrieve
			{
				clearTypeBox();
				clearSuggBox();
				gotoxy(15, 9);
				std::cout << "Enter file name: ";
				std::cin >> fileName;
				location = decode(words, genHuffTree(words, false, fileName), fileName);
				break;
			}
			case' ':		//word complete [GIVE NO SUGGESTIONS]
			{
				gotoxy((location % 52) + 1, (location / 52) + 2);
				std::cout << ' ';
				++location;
				words.push_back(word);
				word = "";
				clearSuggBox();
				selected = 0;
				break;
			}
			case 27:
			{
				words.push_back(word);
				clearTypeBox();
				gotoxy(13, 8);
				std::cout << "Any unsaved text will be lost.";
				gotoxy(13, 9);
				std::cout << "Do you want to exit? [Y/N]";
				char x;
				while (1)
				{
					x = _getch();
					if (x == 'Y' || x == 'y' || x == 'N' || x == 'n')
						break;
				}
				clearTypeBox();
				if (x == 'N' || x == 'n')
				{
					location = typeWords(words);
					break;
				}
				gotoxy(13, 9);
				std::cout << "Thankyou for using our NotePad!";
				gotoxy(1, screenHeight + 3);
				return;
			}
			case '+':		//new doc
			{
				clearTypeBox();
				words.clear();
				clearSuggBox();
				word = "";
				location = 0;
				break;
			}
			default:
			{
				gotoxy((location % 52) + 1, (location / 52) + 2);
				std::cout << input;

				++location;
				word += input;
				suggestions = getSuggestions(word, dictionary);
				NOfSugg = suggestions.size();
				if (NOfSugg > 10)
					NOfSugg = 10;
				clearSuggBox();
				if (NOfSugg != 0)
				{
					j = 3;
					t = suggestions.size();
					for (int i = 0; i < t && j < 13; ++i)
					{
						if ((j - 3) == selected)
							Color(1);	//blue
						else
							Color(7);	//white
						gotoxy(57, j);
						std::cout << word << suggestions[i];
						++j;
					}
					Color(7);
				}
				else
					clearSuggBox();
			}
			}
	}
}