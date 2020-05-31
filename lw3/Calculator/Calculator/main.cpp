#include <iostream>

#include "CCalculatorControl.h"

using namespace std;

int main()
{
	CCalculator calc;
	CCalculatorControl calculatorControl(calc, cin, cout);

	while ((!cin.eof()) && (!cin.fail()))
	{
		if (!calculatorControl.ExecuteCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
}