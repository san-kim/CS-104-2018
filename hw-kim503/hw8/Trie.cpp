#include "Trie.h"
#include <iostream>
#include <fstream>

using namespace std;

// a constructor for an empty trie
TrieSet::TrieSet() 
{
	TrieNode* r = new TrieNode();
	r->parent = NULL;
	r->inSet = false;
	//initialize all as null
	for(int i = 0; i<26; i++)
	{
		r->children[i] = NULL;
	}
	rootNode = r;
}

// destructor
TrieSet::~TrieSet()
{
	destructorHelper(rootNode);
}

//essentially a post order traversal deletion so nodes with no children of their own are deleted first 
void TrieSet::destructorHelper(TrieNode* start)
{
	for(int i = 0; i<26; i++)
	{
		//if the node has a child
		if(start->children[i] != NULL)
		{
			//keep going down/outwards
			destructorHelper(start->children[i]);
		}
	}
	//if it has no other children of its own, then delete it
	delete start;
}

/* Add this string to the set.
      Do nothing if the string is already in the set. */
void TrieSet::insert (std::string input)
{
	//starting from the root node, traverse trie character by character from the root node
	TrieNode* currentNode = rootNode; 
	for(unsigned int i = 0; i<input.size(); i++)
	{
		//find index of where the letter of the string would go
		int childindex = toupper(input[i]) - 'A';
		//if that letter doesn't exist yet, then add it as a node
		if(currentNode->children[childindex] == NULL)
		{
			TrieNode* addedNode = new TrieNode();
			//parent is the current node
			addedNode->parent = currentNode;
			addedNode->inSet = false;
			//initialize all addedNode's children as null
			for(int j = 0; j<26; j++)
				addedNode->children[j] = NULL;
			//set the added letter in the trie
			currentNode->children[childindex] = addedNode;
		}
		//otherwise still traverse out the trie
		currentNode = currentNode->children[childindex];
	}

	//set the last Node's/letter's inSet as true
	currentNode->inSet = true;
}

/* Removes this string from the set.
      Do nothing if the string is not already in the set. */
void TrieSet::remove (std::string input)
{
	if(input.size() == 0)
	{
		return;
	}

	//find where the node should be by traversing the trie
	TrieNode* currentNode = rootNode; 
	for(unsigned int i = 0; i<input.size(); i++)
	{
		//find index of where the letter of the string would go
		int childindex = toupper(input[i]) - 'A';
		//error case if it isn't contained in the trie and we are trying to remove it anyways
		if(currentNode->children[childindex] == NULL)
			return;
		//otherwise traverse down
		currentNode = currentNode->children[childindex];
	}

	bool isPrefixItself = false;
	for(int i = 0; i<26; i++)
	{
		//if the last node of the string is the prefix of another string
		//if one of the last letter's children is not NULL
		if(currentNode->children[i] != NULL)
		{
			isPrefixItself = true;
		}
	}
	

	//set the last node's inSet value as false as 
	currentNode->inSet = false;
	//if it is a part of a longer word, then just set the inSet as false and do nothing else
	if(isPrefixItself)
	{
		return;
	}

	//otherwise delete on way up if we can
	for(unsigned int i = input.size()-1; i>=0; i--)
	{
		//checks whether we can delete this node, or if it has other children in which case we cant
		bool hasOtherChildren = false;
		for(int i = 0; i<26; i++)
		{
			if(currentNode->children[i] != NULL)
			{
				hasOtherChildren = true;
			}
		}
		//if the node we are looking at has other children or if this is another smaller word, stop deleting 
		if(hasOtherChildren || currentNode->inSet == true)
		{
 			break;
		}

		//if it is childrenless, aka we should delete this node, work our way up, should never delete root
		currentNode = currentNode->parent;
		if(currentNode == NULL)
			return;
		//delete the allocated memory of that letter / child
		delete currentNode->children[(int)(toupper(input[i]) - 'A')];
		//reset the parent's children array location of that child as NULL
		currentNode->children[(int)(toupper(input[i]) - 'A')] = NULL;
	}
}
   

/* returns the TrieNode matching the provided string, or returns NULL 
      if it is not the prefix of a word in the Trie. */
TrieNode* TrieSet::prefix(std::string px)
{
	TrieNode* currentNode = rootNode; 
	for(unsigned int i = 0; i<px.size(); i++)
	{
		//find index of where the letter of the string would go
		int childindex = toupper(px[i]) - 'A';
		//if that child doesn't exist, then return null as it is not a prefix
		if(currentNode->children[childindex] == NULL)
			return NULL;
		//otherwise traverse down
		currentNode = currentNode->children[childindex];
	}

	return currentNode;
}

TrieNode* TrieSet::getRootNode()
{
	return rootNode;
}

//returns next trienode, if it's NULL, it means it DNE
TrieNode* TrieSet::getChildNode(TrieNode* currentNode, char nextLetter)
{
	int childindex = toupper(nextLetter) - 'A';
	return currentNode->children[childindex];
}

//populates trie with the dictionary file
void TrieSet::populateTrie(string dictionary_File)
{
	//read in the dictionary file
	ifstream dictionaryfile(dictionary_File);
	if(dictionaryfile.fail())
		return;
	//initialize wordList in uppercase alphabetical order
	string word;
	while(dictionaryfile >> word)
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
		//in uppercase alphabetical order at this point, insert entire dictionary
		this->insert(word); 
		//consume rest of line
		getline(dictionaryfile, word);
	}
}
