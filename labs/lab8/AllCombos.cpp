#include "AllCombos.h"
#include <string>
#include <iostream>

using namespace std;

//you may write any helper functions you need
//1: set
//2: map of key = letter grade, value = set of students who got that grade

string helper(vector<string>* result, string append, string input, int k);

void AllCombos(vector<string>& result, string input, int k)
{
	string append = "";
	helper(&result, append, input, k);
}

string helper(vector<string>* result, string append, string input, int k)
{
	if(k == 0)
	{
		result->push_back(append);
		return "";
	}

	for(unsigned int i = 0; i<input.size(); i++)
	{
		string temp = helper(result, append+input[i], input, k-1);
	}
	return "";
}