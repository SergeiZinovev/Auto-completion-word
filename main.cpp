#include "TrieDictionary.h"
#include <string>



int main()
{
	// fill in the dictionary
	TrieNode* trieWord = new TrieNode();
	insert(trieWord, "apple");
	insert(trieWord, "aim");
	insert(trieWord, "ashtray");
	insert(trieWord, "ask");
	insert(trieWord, "add");
	insert(trieWord, "also");
	insert(trieWord, "aid");
	insert(trieWord, "porsche");
	insert(trieWord, "appropriate");
	insert(trieWord, "gum");
	insert(trieWord, "golf");


	std::string wordVariants;// a variable for all variants of words for auto-substitution
	wordVariants.clear();    // clean it 
	std::string VersionWord;  // a variant of the selected word from the suggested auto-substitution
	std::string inputWord;    // entered word
	std::string fullText;     // all that the user entered
	std::string tempWord;     // a variable to store unprocessed words 
	bool space = true;           // spaces check
	while (std::cin)  // the program will run until the user closes the terminal
	{

		
		getline(std::cin, inputWord);

		for (size_t i = 0, ib = 0; i < inputWord.length(); ++i)// fill with the entered text 
		{

			fullText.push_back(inputWord[i]);
			tempWord.push_back(inputWord[i]);

			if (inputWord[i] == ' ')  // if the user has finished typing the word
			{
				tempWord.clear();    // remove it from unprocessed words
			}

		}
		wordSubstitution(trieWord, wordVariants, tempWord); // send the unfinished word to the word search for autocomplete
		if (wordVariants.empty())  // if there are no options in the dictionary
		{
			tempWord.clear();
			std::cout << fullText;
			continue;
		}
		wordVariants.erase(wordVariants.length() - 1); // erase space
		int choice = 1;                      // variant numbering
		std::cout << std::endl << choice << " ";
		for (size_t i = 0; i < wordVariants.length(); ++i)  // display the options on the screen
		{
			if (wordVariants[i] == ' ')
			{
				choice++;
				std::cout << std::endl << choice;
			}
			std::cout << wordVariants[i];
		}
		std::cout << "\nSelect the appropriate word by pressing 1, 2 or 3. If there is no such word, press 0\n";  // suggest that you choose the option

		std::cin >> choice;
		std::cin.ignore(32767, '\n');
		for (size_t i = 0; i < wordVariants.length(); ++i)  //  the selected word into VersionWord
		{
			if (choice == 1)
			{
				VersionWord.push_back(wordVariants[i]);

			}
			if (wordVariants[i] == ' ')
			{
				--choice;
			}
			if (choice < 1)
			{

				break;
			}
		}

		if (!VersionWord.empty())  // If the user has selected any option
		{
			fullText.erase(fullText.length() - tempWord.length());
			fullText += VersionWord;
			tempWord.clear();
			std::cout << fullText;
		}
		else                                 // If not selected 
			std::cout << fullText;

		wordVariants.clear();
		VersionWord.clear();



	}
	return 0;
}

