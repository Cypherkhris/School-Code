#ifndef HEADER_H
#define HEADER_H

#include<iostream>
#include <string>

using namespace std;
// Class InfixToPostfix
class InfixToPostfix
{
public:
	InfixToPostfix();
	bool IsOperand(char c);
	bool IsOperator(char c);
	int GetOperatorWeight(char op);
	int HasHigherPrecedence(char op1, char op2);
	int PerformOperation(char operation, int operand1, int operand2);
	bool IsNumericDigit(char c);
	bool IsAlphabet(char c);
	int evalPost(string item);
	string infToPost(string item);
};

#endif // End file 
