#include "Dictionary.h"
#include <fstream>
#include <iostream>

using namespace std;


/* The constructor gets passed the name of the file from which
	   to read the word list. */
Dictionary::Dictionary (string dictionary_file_name)
{
	ifstream dictionary_file(dictionary_file_name);
	
	//initialize wordList in lowercase alphabetical order
	string word;
	while(dictionary_file >> word)
	{
		//convert to uppercase for uniformity
		for(int i = 0; i<(int)word.size(); i++)
		{
			word[i] = toupper(word[i]);
			if(isspace(word[i]))
			{
				break;
			}
		}
		wordList.insert(word); //in lowercase alphabetical order at this point
		//consume rest of line
		getline(dictionary_file, word);
	}
	//wordList is now in order and uppercase
}

Dictionary::~Dictionary ()
{

}

/* Checks whether the given word is in the dictionary, and returns true if so.
   Case should not matter. Must run in O(logn) for the number of words in the dictionary. */
bool Dictionary::isLegalWord (string const & word) const
{	
	set<string>::iterator it;
	//set to upper case
	string inptword = word;
	for(int i = 0; i<(int)inptword.size(); i++)
	{
		inptword[i] = toupper(word[i]);
	}
	// find() is logarithmic time O(logn)
	it = wordList.find(inptword);
	//if it is within the wordList set
	if(it != wordList.end())
	{
		return true;
	}

	else
	{
		return false;
	}
}
