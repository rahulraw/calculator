
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <unordered_map>
#include <string>
#include <iomanip>
#include "Calculator.h"

using namespace std;

/* go to Calculator.cpp to checkout the cool stuff */
int main()
{
	string equation = "";
	Calculator* myCalc = new Calculator;
	while(true)
	{
		cout << "Enter your expression: ";
		getline(cin,equation);
		if(equation == "quit")
			return 0;
		double result = myCalc->solve(equation);
		cout <<"result is : " << result << endl;
	}
	return 0;
}