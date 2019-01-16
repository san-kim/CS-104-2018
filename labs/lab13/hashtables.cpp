#include "hashtables.h"

#include <utility>
#include <vector>
#include <string>
#include <cctype>
#include <iostream>
#include <unordered_map>

using namespace std;

//case does not matter
//ignore special characters ie. only consider letters a-z

bool isAnagram(std::string s, std::string t) 
{
	unordered_map<char,int> letterMap;
	//initialize all letters to 0 in map
	for(int i = 0; i<26; i++)
	{	
		//set letter of alphabet to 0
		letterMap.insert(make_pair((char)('a'+i), 0));
	}

	//set all of s in lettermap
	for(unsigned int i = 0; i<s.size(); i++)
	{
		//increment by 1 if a letter
		if(tolower(s[i]) <= (int)'z' && tolower(s[i]) >= (int)'a')
		{
			letterMap[(char)(tolower(s[i]))]++;
		}
	}	

	//check with t
	for(unsigned int i = 0; i<t.size(); i++)
	{
		//if this lette is not a-z in the other letter, continue to next
		if(!(tolower(t[i]) - (int)'a' >= 0))
		{
			continue;
		}	

		if(tolower(t[i]) - (int)'a' >= 0)
		{	
			if(letterMap[(char)(tolower(t[i]))] <= 0)
			{
				return false;
			}
		}

		else
		{
			if(tolower(t[i]) <= (int)'z' && tolower(t[i]) >= (int)'a')
			{
				letterMap[(char)(tolower(t[i]))]--;
			}
		}
	}

    return true;
}

//output FIRST pair found

pair<int, int> twoSum(vector<int> input, int target) 
{
	int max = input[0];
	for(unsigned int i = 0; i<input.size(); i++)
	{
		if(max < input[i])
			max = input[i];
	}


	unordered_map<int, int> numberIndex;
	for(int i = 0; i<max; i++)
	{
		//set to index -1 so we know which exist and which dont
		numberIndex.insert(make_pair(i,-1));
	}

	//store int value,index
	//update how many each has
	for(unsigned int i = 0; i<input.size(); i++)
	{
		numberIndex[input[i]] = i;
	}

	for(unsigned int i = 0; i<input.size(); i++)
	{
		//if not in bounds, if the result is not even in the range of the inputs
		if(target - input[i] < 0 || target - input[i] > max)
		{
			continue;
		}

		//if subtracted value exists
		if(numberIndex[target - input[i]] != -1)
		{
			//index i and index of the subtracted value
			cout << max << "   " << target - input[i] << endl;
			return make_pair(i, numberIndex[target - input[i]]);
		}
	}

    return make_pair(-1, -1);
}