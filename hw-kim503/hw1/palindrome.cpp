/**
 * Incorrect code to identify palindromes
 */

#include <iostream>
#include <sstream>
#include <cstring> 

bool helper (std::stringstream &input, int len)
{
	char prev; 

	//if we are at the midpoint of the string, return true.
	if (len == 0) return true;

	/**
	 * If the length of the string is odd, and the next
	 * character is the midpoint of the string, consume it
	 * and return true.
	 */
	input >> prev;
	if (len == 1) return true;

	bool val = helper(input, len-2);

	//make your changes only below this line.
	char next;
	input >> next;
	if (prev == next && val) return true;

	return false;
}

//do not change the main function.
int main (int argc, char* argv[])
{
  if(argc < 2){
    std::cerr << "Please provide a string of characters." << std::endl;
    return 1;
  }
  std::stringstream ss;
  ss << argv[1];
  if(helper(ss, static_cast<int>(strlen(argv[1]))))
	  std::cout << "Palindrome" << std::endl;
  else std::cout << "Not a Palindrome" << std::endl;
  return 0;
}
