#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stackint.h"

using namespace std;

int valueInParenthesis(StackInt& stack);
bool is_integer(char input);
bool is_operator(char input);
int operator_to_int(char input);
bool isOnlyWhiteSpace(string equation);


int main(int argc, char* argv[])
{
	if(argc != 2) {
		return 1;
	}

	ifstream ifile(argv[1]);
	if(ifile.fail()) {
		return 1;
	}

	string equation = "";
	while(getline(ifile, equation))
	{
		//instantiate stack used for this equation line
		StackInt stack;
		//if it is an empty line
		if(equation.size() == 0) {
			continue;
		}

		bool onlyWhiteSpace = isOnlyWhiteSpace(equation);
		if(onlyWhiteSpace) {	//ignore the line that is just whitespace
			continue;
		} 
		//give the getline to a stringstream
		stringstream ss;
		ss << equation;
		//read each character by element, find later whether it's int or +/*
		char element;
		// for if it was Malformed within this inner while loop
		bool broken = false;
		//while it can read elements, aka read until it can't
		while(ss >> element)
		{
			//ignore whitespace
			if(isspace(element)) {
				continue;
			}
			//if we read something that is neither an integer nor an operator
			if(is_integer(element)==false && is_operator(element)==false)
			{
				cout << "Malformed" << endl;
				broken = true;
				break;
			}
			//at this point onwards the element is either an integer or 
			//an operator if the element read is an integer value
			if(is_integer(element))
			{
			//integer reader reads every new digit as its new ones value
				int IntegerInput = (int)element - '0';
				//to check the next element whether it is an int or not
				ss >> element;
				//if it fails, the singular number was the last int value
				if(ss.fail())
				{
					stack.push(IntegerInput);
					break;
				}
				//to break the larger loop in the while below
				bool integerEndsInput = false;
				//keep reading until element is not an integer
				while(is_integer(element))
				{
					//multiply the previous value by 10 and add new value
					IntegerInput = IntegerInput*10 + ((int)element - '0');
					ss >> element;
					//where an integer ends getline & is last thing but longer 
					//than one number long, integerEndsInput breaks 2nd while
					if(ss.fail())
					{
						integerEndsInput = true;
						stack.push(IntegerInput);
						break;
					}
				}
				//case where int ends the line, should go to next line, 
				//integer has been pushed already
				if(integerEndsInput) {
					break;
				} 
				//regular case 
				stack.push(IntegerInput);
			}
			//this operation above will read in one extra element if succeeds
			//works even if the if reads an extra element, unless it ended
			if(is_operator(element) == true)
			{
				int operatorToint = operator_to_int(element);
				stack.push(operatorToint);
				//if our input is a closed parenthsis
				if(operatorToint == operator_to_int(')'))
				{
					//will do the popping within the function
					//this will check whether there are too many ')'s 
					int result = valueInParenthesis(stack);
					if(result == -1)
					{
						cout << "Malformed" << endl;
						broken = true;
						break;
					}
					//the valueInParenthesis function will pop everything from )
					//to ( and return the result if it is not malformed.
					else
					{
						stack.push(result);
					}
				}
			}
		}
		//if it was malformed within inner while loop, skip to next eq
		if(broken)
		{
			continue;
		}
		//When we get to here, SHOULD have only shifts and our integer result 
		//from all our paren ops, we took care of every ) as it came in
		// any open parenthesis, +, or * should be counted as a malformation
		int answer = -10000; 
		//our top of the stack SHOULD ALWAYS be an integer 
		//result of all of the paren ops if there were any
		if(!(stack.top() >= 0) )
		{
			cout << "Malformed" << endl;
			//to next equation
			continue;
		}
		if(stack.top() >= 0)
		{
			answer = stack.top();
		}
		//last integer is stored in "answer", now pop to see if anything after
		stack.pop();
		//if it was only thing in the stack
		//SUCCESS!!!
		if(stack.empty())
		{
			cout << answer << endl;
			continue;
		}
		//for if we find a malformation in this while loop
		bool brokeAgain = false;
		while(!stack.empty())
		{	
			//there should be NO more open parens, +, *, or Integers left
			if(stack.top() == -1 || stack.top() == -3 || 
				stack.top() == -4 || stack.top() >= 0)
			{
				cout << "Malformed" << endl;
				brokeAgain = true;
				break;
			}			
			//if there is a legal leftshift found on top of stack
			else if(stack.top() == operator_to_int('<'))
			{	
				stack.pop();
				answer = answer*2;
				//if consuming < finishes the eq legally & empties the stack,
				// SUCCESS!!!!!, ex: "<<(1+2+3+4)" -> "<<10" -> "<<" = "<" = 40
				if(stack.empty())
				{
					cout << answer << endl;
					brokeAgain = true;
					break;
				}
			}
			//if there is a legal rightshift found on top of stack
			else if(stack.top() == operator_to_int('>'))
			{	
				stack.pop();
				answer = answer/2;
				//if consuming a > finishes the eq legally & empties the stack,
				// SUCCESS!!!!!
				if(stack.empty())
				{
					cout << answer << endl;
					brokeAgain = true;
					break;
				}
			}

		//these if's should cover all cases so if top is anything else, malform
			else {
				cout << "Malformed" << endl;
				brokeAgain = true;
				break;
			}
		}
		//this while loop should succeed and break or malform and break at this
		//point as we already consumed the parenthetical right most result & we
		//are just doing shift operations and checking whether any malformed +,
		// (, *, or integers remain. in the case where it malformed or succeeded
		// within above while loop
		if(brokeAgain) {
			continue;
		}
	}
	return 0;
}


//do operations within parenthesis when a ')' is found
//will be called for the first ')' found, shouldnt have any ()'s in them'
int valueInParenthesis(StackInt& stack) {
	//pop the closed parenthesis, this should always be true when called
	if(stack.top() == operator_to_int(')')) {
		stack.pop();
	}
	//if it is the case that it is empty ()
	if(stack.top() == operator_to_int('(')) {
		stack.pop();
		return -1;
	}
	//missing open parenthesis, malformed
	if(stack.empty()) {
		return -1;
	}	
	bool isRightmostElement = true;
	bool isFirstOperator = true;
	// checks that one exists and is consistent thru the parenthesis
	int operatorType = -100;
	int result = -10;
	//keep looping until it finds an ( or errors
	while(stack.top() != operator_to_int('(')) {
	//element is current reading element, stack.top() is the next one after pop
		int element;
		if(isRightmostElement) {
			element = stack.top();
			stack.pop();
		}
		//also if it goes to empty without succeeding, means failure
		if(stack.empty() == true) {
			return -1;
		}
		//if this is the first, rightmost element being read
		if(isRightmostElement) {
			if(!(element >= 0)) {  //if it is not an integer, malformed
				return -1;
			}
			//if integer was the only thing in the parens ex:(123), malformed
			if(stack.top() == operator_to_int('(')) {
				return -1;
			}
			isRightmostElement = false;
			result = element; //set result for the first time
			//if the very rightmost integer has shifts right after it
			//we just increment result here, is just the first integer shifted
			while(stack.top() == -5 || stack.top() == -6) {
				if(stack.top() == operator_to_int('<')) { //if shift left
					//pop the shift operand, the integer element already popped
					stack.pop();
					//missing open parenthesis, malformed: ex <<3)
					if(stack.empty() == true) {
						return -1;
					}
					result = result*2; //multiply result by 2 to keep track
				}
				//if shift right
				if(stack.top() == operator_to_int('>')) {
					//pop the shift operand, the integer element already popped
					stack.pop();
					//missing open parenthesis, malformed: ex >>3)
					if(stack.empty() == true) {
						return -1;
					}
					result = result/2; //divide result by 2 to keep track
				}
			}
			//result is shifted (if is the case) first rightmost integer
			//if it is the case that input is something like (<<8)
			if(stack.top() == operator_to_int('(')) {
				return -1;
			}
			//if it is the case that (5>>4)
			if(stack.top() >= 0) {
				return -1;
			}
		}

		//if it is the first + or *, store to error check for mixing operators
		if(isFirstOperator && (stack.top() == -3 || stack.top() == -4)) {
			operatorType = stack.top();
			isFirstOperator = false;
		}
		//we now know there is an integer at rightmost part of the eq in parens
		//after second iteration we should know the operator
		element = stack.top();
		stack.pop();
		if(stack.empty() == true) {
			return -1;
		}
		//from here on out, we will want to read OPERATOR and Integer pairs with
		//which we append its output to result so our current "element" is 
		//should always be an operand after the first element, ALL new inputs 
		//should now be operands + or *
		if(!isRightmostElement && element != -3 && element != -4) {
			return -1;
		}
		if(element == -3 || element == -4) { //if + or *
			//if the next element is NOT an integer or at the end at (, 
			//then malformed in all cases as (+5) and (5++4) will be malformed
			//we already popped element, so the next element is just stack.top()
			if(stack.top() == operator_to_int('(') || !(stack.top() >= 0)) {
				return -1;
			}
			//if the operator is not the first one, mixing operators, malformed
			if(element != operatorType) {
				return -1;
			}
			//regular cases where it is of legal usage (finally)where the next 
			//element after the operator is an integer, top is an int
			//if it is PLUS
			if(element == -3) {
				int addend = stack.top();
				stack.pop(); //pop the addend
				//missing open parenthesis, malformed: ex 3+6)
				if(stack.empty() == true) {
					return -1;
				}
				//if the addend has shift(s) after it
				while(stack.top() == -5 || stack.top() == -6) {
					//if shift left
					if(stack.top() == operator_to_int('<')) {
						stack.pop();  //pop the shift operand
						//missing open parenthesis, malformed: ex <<3+6)
						if(stack.empty() == true) {
							return -1;
						}
						addend = addend*2;
					}
					if(stack.top() == operator_to_int('>')) {  //if shift right
						stack.pop();  //pop the shift operand
						//missing open parenthesis, malformed: ex >>3+6)
						if(stack.empty() == true) {
							return -1;
						}
						addend = addend/2;
					}
				}
				//if is case that (5>>4+9) 9,+ consumed, (5>>4) -> (5) malformed
				//stack.top() SHOULD BE OPERATOR namely + here or ( if finished
				if(stack.top() >= 0) {
					return -1;
				}
				//if it is the legal end
				if(stack.top() == operator_to_int('(')) {
					stack.pop(); //pop the open parenthesis
					return result + addend;
				}
				//if there is another + operation after that
				//if it is *, will return -1 next iteration
				if(stack.top() == operator_to_int('+')) {
					result = result + addend;
				}
			}
			//if it is MULTIPLY
			else if(element == -4) {  
				int multiplicand = stack.top();
				stack.pop(); //pop the multiplicand
				//missing open parenthesis, malformed: ex 3*6)
				if(stack.empty() == true) {
					return -1;
				}
				//if the multiplicand has shift(s) after it
				while(stack.top() == -5 || stack.top() == -6) {
					if(stack.top() == operator_to_int('<')) { //if shift left
						stack.pop();//pop the shift operand
						//missing open parenthesis, malformed: ex <<3*6)
						if(stack.empty() == true) {
							return -1;
						}
						multiplicand = multiplicand*2;
					}
					//if shift right
					if(stack.top() == operator_to_int('>')) {
						//pop the shift operand, integer already popped at start
						stack.pop();
						//missing open parenthesis, malformed: ex >>3*6)
						if(stack.empty() == true) {
							return -1;
						}
						multiplicand = multiplicand/2;
					}
				}
				//if case that (5>>4*9) 9,*,(5>>4),>>4 consumed,(5)malformed
				//stack.top() SHOULD BE OPERATOR namely * here or ( if finished
				if(stack.top() >= 0) {
					return -1;
				}
				//if it is the legal end
				if(stack.top() == operator_to_int('(')) {
					stack.pop(); //pop the open parenthesis
					return result * multiplicand;
				}
				//if there is another * operation after that
				//if it is +, will return -1 next iteration
				if(stack.top() == operator_to_int('*')) {
					result = result * multiplicand;
				}
			}
		}
	}
	return -1; //assume malformed if it got to here?
}


//returns true if the char input is an integer between 0-9
bool is_integer(char input)
{
	if((int)input - '0' >= 0 && (int)input - '0' <= 9)
	{
		return true;
	}
	return false;
}
//returns true is the input is one of our 
bool is_operator(char input)
{ 
	if(input == '<' || input == '>' || input == '(' || input == ')' 
		|| input == '+' || input == '*')
	{
		return true;
	}
	return false;
}

int operator_to_int(char input)
{
	if(input == '(')
	{
		return -1;
	}

	else if(input == ')')
	{
		return -2;
	}

	else if(input == '+')
	{
		return -3;
	}

	else if(input == '*')
	{
		return -4;
	}

	else if(input == '<')
	{
		return -5;
	}

	else if(input == '>')
	{
		return -6;
	}

	//error case
	else
	{
		return -100;
	}
}

//if the equation is only whitespace, return true.
bool isOnlyWhiteSpace(string equation)
{
	for(unsigned int i = 0; i<equation.size(); i++)
	{
		//if it is not a whitespace, return false
		if(!(isspace(equation[i])))
		{
			return false;
		}
	}
	return true;
}