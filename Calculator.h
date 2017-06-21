#ifndef CALCULATOR_H
#define CALCULATOR_H

using namespace std;

class Calculator
{
	private:
		unordered_map <char, int> opPrecedence =
		{
			{'&',5},
			{'|',4},
			{'*',3},
			{'/',3},
			{'+',2},
			{'-',2}
		};
		bool isNumber(char c);
		bool isNumber(std::string& s);
		bool isOperator (char c);
		void debugShuntYard(char c,deque<string> out_queue, stack<char> op_stack);
		deque <string> makePostfix(string eq);
		double solvePostfix(deque <string> eq);
	public:
		Calculator();
		double solve(string eq);
};

#endif