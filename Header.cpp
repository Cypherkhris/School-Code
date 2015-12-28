#include <iostream>
#include "Header.h" 
#include "Stack.h"
// implementation infixToPostfix
using namespace std;

InfixToPostfix::InfixToPostfix()
{

}

bool InfixToPostfix::IsOperand(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

bool InfixToPostfix::IsOperator(char c)
{
	if (c == '+' || c <= '-' || c == '*' || c == '/')
		return true;
	return false;
}

int InfixToPostfix::GetOperatorWeight(char op)
{
	int weight = -1;
	switch (op)
	{
		case '+':
		case '-':
			weight = 1;
		case '*':
		case '/':
			weight = 2;
	}
	return weight;
}

int InfixToPostfix::HasHigherPrecedence(char operator1, char operator2)
{
	int operator1Weight = GetOperatorWeight(operator1);
	int operator2Weight = GetOperatorWeight(operator2);

	return operator1Weight>operator2Weight?true:false;
}

int InfixToPostfix::PerformOperation(char operation, int operand1, int operand2)
{
	if (operation == '+')return operand1 + operand2;
	else if (operation == '-')return operand1 - operand2;
	else if (operation == '*')return operand1*operand2;
	else if (operation == '/')return operand1 / operand2;
	else cout << "Unexpected Error\n";
	return -1;
}

bool InfixToPostfix::IsNumericDigit(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

bool InfixToPostfix::IsAlphabet(char c)
{
	if (c >= 'a'&& c <= 'z' || c >= 'A'&& c <= 'Z')
		return true;
	return false;
}

int InfixToPostfix::evalPost(string item)
{
	Stacks stack;
	for (int i = 0; i < item.length();i++)
	{
		if (item[i] == ' ' || item[i] == ',')continue;
		else if (IsOperator(item[i]))
		{
			int op2 = stoi(stack.stackTop()); stack.pop();
			int op1 = stoi(stack.stackTop()); stack.pop();

			int result = PerformOperation(item[i], op1, op2);
			stack.push(to_string(result));
		}
		else if (IsNumericDigit(item[i]))
		{
			int op = 0;
			while (i<item.length() && IsNumericDigit(item[i]))
			{
				op = (op * 10) + (item[i] - '0');
				i++;
			}
			i--;
			stack.push(to_string(op));
		}
		else if (IsAlphabet(item[i]))
		{
			char alp = ' ';
			while (i < item.length() && IsAlphabet(item[i]))
			{
				alp +=item[i];
				i++;
			}
			i--;
			stack.push(to_string(alp));
		}
	}
	return stoi(stack.stackTop());
}

string InfixToPostfix::infToPost(string item)
{
	Stacks stack;
	string postFix = " ";
	for (int i = 0; i < item.length();i++)
	{
		cout << postFix << endl;
		if (item[i] == ' ')
			postFix += item[i];
		else if (IsOperator(item[i]))
		{
			while (!stack.empty() && stack.stackTop()!="(" &&HasHigherPrecedence(*(stack.stackTop().c_str()), item[i]))
			{
				postFix += stack.stackTop();
				stack.pop();
			}
			stack.push(string(1, item[i]));
		}
		else if (IsOperand(item[i]))
		{
			postFix += item[i];
		}
		else if (item[i]=='(')
		{
			stack.push(string(1,item[i]));
		}
		else if(item[i]==')')
		{
			while (!stack.empty() && stack.stackTop() != "(" &&HasHigherPrecedence(*(stack.stackTop().c_str()), item[i]))
			{
				postFix += stack.stackTop();
				stack.pop();
			}
			stack.pop();
		}
	}
	while (!stack.empty())
	{
		postFix += stack.stackTop();
		stack.pop();
	}
	return postFix;
}
