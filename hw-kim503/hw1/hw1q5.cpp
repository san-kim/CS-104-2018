#include <iostream>
#include <sstream>
#include <cstring> 
#include <fstream>

using namespace std;

int main (int argc, char* argv[])
{
	if(argc < 2) 
	{
		//cerr << "Please provide an input txt file." << endl;
		return 1;
	} 

	//read file and check that it exists
    ifstream ifile(argv[1]);
    if(ifile.fail()) 
    {
    	//cerr << "Unable to open file." << endl;
    	return 1;
    }

    int wordCount;
    ifile >> wordCount;
    if(ifile.fail()) 
    {
    	//cerr << "No number at the top." << endl;
    	return 1;
    }

    //if there are no words, just exit here
    if(wordCount == 0) 
    {
    	//cout << endl;
    	return 0;
    }

    //to go to next line after integer
    string line;
    getline(ifile, line);
    if(ifile.fail()) 
    {
    	//cout << "Bad formatting." << endl;
    	return 1;
    }

    //dynamically allocate an array of strings
    string* words = new string[wordCount];

    //read into words however many words as specified
    for(int i = 0; i<wordCount; i++)
    {
    	string w;
    	ifile >> w;
    	//in case there are not enough words as specified
    	if(ifile.fail())
    	{
    		delete [] words;
    		cout << "Not enough words." << endl;
    		return 2;
    	}

    	words[i] = w;
    }

    //in the case where the file contains more words than specified
    string extraCase;
    ifile >> extraCase;
    //if this succeeds
    if(!ifile.fail())
    {
    	delete [] words;
    	cout << "More words than specified." << endl;
    	return 2;
    }


    for(int i = wordCount-1; i >= 0; i--)
    {
    	cout << words[i] << endl;
    }

    //delete dynamically allocated words
    delete [] words;

	return 0;
}