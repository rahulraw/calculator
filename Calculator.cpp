#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <unordered_map>
#include <string>
#include <iomanip>
#include "Calculator.h"

#define DEBUG 0
using namespace std;


bool Calculator::isNumber(char c)
{
			return (c >= '0' && c <= '9');
}

bool Calculator::isNumber(std::string& s)
{
    int period_cnt = 0;
    for(int i = 0; i < s.size();i++)
    {
    	if (s[i] == '.') 
    		period_cnt++;

    	if (std::isdigit(s[i]) || (s[i] == '.' && period_cnt <= 1) || s[i] == 'u')
    	{
    		if (s[i] == 'u')
    			s[i] = '-';
    		continue;
    	}
    	else
    		return false;
    }
    return true;
}

bool Calculator::isOperator(char c)
{
	return (c == '*' ||
			c == '/' ||
			c == '+' ||
			c == '-' ||
			c == '&' ||
			c == '|' );
}

void Calculator::debugShuntYard(char c,deque<string> out_queue, stack<char> op_stack)
{
	cout << setw(10) << "out_queue: ";
	if(!out_queue.empty())
		for(int i = 0;i < out_queue.size();i++)
			cout << "[" << out_queue[i] << "]";
	cout << endl << setw(10) << "op_stack on top: ";
	if(!op_stack.empty())	
		cout << op_stack.top() << "  size: " << op_stack.size(); 
	cout << endl << endl;
}		
		
deque <string> Calculator::makePostfix(string eq) // using Shunt Yard algorithm
{
	stack < char > op_stack;
	deque < string > out_queue;
	string numstr;
	char lastchar = ' ';
	for(char& c: eq) 
	{
		if((isOperator(c) && !numstr.empty()) || c == ')')
		{
			out_queue.push_back(numstr);
			numstr.clear();
		}
		if(isNumber(c) || c == '.')
		{
			numstr.push_back(c);
			if(&c == &eq.back())
			{
				out_queue.push_back(numstr);
				numstr.clear();
			}
		}
		else if(c == '-' && (isOperator(lastchar) || lastchar == '(' || &c == &eq.front()))
				numstr.push_back('u');
		else if(isOperator(c))
		{
			if(!op_stack.empty())
				while(opPrecedence[op_stack.top()] > opPrecedence[c])
				{
					string s;
					s.push_back(op_stack.top());
					out_queue.push_back(s);
					op_stack.pop();
				}
			op_stack.push(c);
		}
		else if(c == '(')
		{
			op_stack.push(c);
		}
		else if(c == ')')
		{
			while(op_stack.top() != '(')
			{
				if(!op_stack.empty())
				{
					string s; 
					s.push_back(op_stack.top());

					out_queue.push_back(s);
					op_stack.pop();
				}
				else
				{
					cout << "Paranthesis mismatched!" << endl;
					out_queue.push_back("ERROR");
					return out_queue;
				}
			}
			op_stack.pop(); // pop left bracket
		}
		else
		{
			cout << "invalid characters!" << endl;
			out_queue.push_back("ERROR");
			return out_queue;
		}
		#if DEBUG
			debugShuntYard(c,out_queue,op_stack);
		#endif
		lastchar = c;
	}
	while(!op_stack.empty())
	{
		string s;
		s.push_back(op_stack.top());
		out_queue.push_back(s);
		op_stack.pop();
	}
	return out_queue;
}

double Calculator::solvePostfix(deque <string> eq)
{
	stack < double > solve_stack;
	for(string str : eq)
	{
		if(isNumber(str))
		{
			solve_stack.push(stod(str)); // note about casting (int)c -> this will only change it to the corresponding ascii num
		}
		else
		{
			char c = str[0];
			double num2 = solve_stack.top();
			solve_stack.pop();
			double num1 = solve_stack.top();
			solve_stack.pop();
			double result;

			switch(c)
			{
				case '&':
					result = (double)(num1 && num2); 
					break;
				case '|':
					result = (num1!=0.0) || (num2!=0.0); 
					break;
				case '*':
					result = num1*num2;	
					break;
				case '/':
					result = num1/num2;
					break;
				case '+':
					result = num1 + num2;
					break;
				case '-':
					result = num1 - num2;
					break;
			}
			solve_stack.push(result);
		}
	}
	return solve_stack.top();
}

Calculator::Calculator()
{
}

double Calculator::solve(string eq)
{
	eq.erase(remove_if(eq.begin(), eq.end(), ::isspace), eq.end());
	deque <string> output = makePostfix(eq);
	#if DEBUG
		for(auto val : output)
			cout <<"["<< val <<"]";
			cout << endl;
	#endif
	if(output.back() == "ERROR")
		return -99999;
	return solvePostfix(output);
}


