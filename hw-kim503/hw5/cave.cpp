#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main(int argc, char* argv[])
{
	cout << "Input a string of directions taken: " << endl;
	string input, result;
	getline(cin,input);
	stringstream ss(input);
	
	for(unsigned int i = 0; i<input.size(); i++){
		if(input[i] != 'n' && input[i] != 'e' && input[i] != 'w' && input[i] != 's'){
			cout << "invalid" << endl;
			return 0;
		}
	}
	if(input.size() == 0)
	{
		cout << "rolled up" << endl;
		return 0;
	}

	else
	{
		char nextletter;
		ss >> nextletter;
		result = nextletter; //first letter read in
		for(unsigned int i = 0; i<input.size(); i++)
		{
			char lastLetter = result[result.size()-1];
			ss >> nextletter;
			if((lastLetter=='e'&&nextletter=='w') || (lastLetter=='w'&&nextletter=='e') || 
			   (lastLetter=='n'&&nextletter=='s') || (lastLetter=='s'&&nextletter=='n'))
			{
				result = result.substr(0,result.size()-1);
			}												//edge cases
			else if(lastLetter != '\0' || i!=input.size()-1)//when it is not empty or is not at end
				result = result + nextletter;
		}
		if(result.size() == 0)
			cout << "rolled up" << endl;
		else
			cout << "not rolled up" << endl;
	} 
}