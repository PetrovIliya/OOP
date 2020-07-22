#include "CCalculatorControl.h"

using namespace std;
using namespace std::placeholders;

CCalculatorControl::CCalculatorControl(CCalculator calculator, istream& input, ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "var", bind(&CCalculatorControl::AddVar, this, _1) },
		{ "let", bind(&CCalculatorControl::SetVarValue, this, _1) },
		{ "fn", bind(&CCalculatorControl::SetFunction, this, _1) },
		{ "print", bind(&CCalculatorControl::PrintIdentifierValue, this, _1) },
		{ "printvars", bind(&CCalculatorControl::PrintVariables, this) },
		{ "printfns", bind(&CCalculatorControl::PrintFunctions, this) }
		})
{
}

bool CCalculatorControl::ExecuteCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
		return true;
	}
	return false;
}

void CCalculatorControl::AddVar(istream& args)
{
	string identifier;
	args >> identifier;
	if (!m_calculator.AddVar(identifier))
	{
		cout << "Invalid name of varible!" << endl;
	}
}

void CCalculatorControl::SetVarValue(istream& args)
{
	string expression;
	args >> expression;
	string firstValue;
	string secondValue;
	if (!ParseStrToValue(expression, firstValue, secondValue) ||
		!m_calculator.SetVarValue(firstValue, secondValue))
	{
		cout << "Invalid expression!" << endl;
	}
}

bool CCalculatorControl::ParseStrToValue(const string& str, string& firstValue, string& secondValue)
{
	auto parsePosition = str.find("=");

	if ((parsePosition == string::npos) || (parsePosition + 1 == str.size()))
	{
		return false;
	}
	firstValue = str.substr(0, parsePosition);
	secondValue = str.substr(parsePosition + 1, str.size());
	return true;
}

void CCalculatorControl::SetFunction(istream& args)
{
	string expression;
	args >> expression;
	string firstValue, secondValue, operand, thirdValue;
	Operator expressionOperator;

	if ((!ParseStrToValue(expression, firstValue, secondValue) ||
		!m_calculator.SetFunction(firstValue, secondValue)) &&
		(!ParseStrToAripthOperation(secondValue, expression, expressionOperator, thirdValue) ||
			!m_calculator.SetFunction(firstValue, expression, expressionOperator, thirdValue)))
	{
		cout << "Invalid expression!" << endl;
	}
}

bool CCalculatorControl::ParseStrToAripthOperation(const string& str, string& firstValue, Operator& operand, string& secondValue)
{
	auto operandPos = string::npos;
	for (auto elem : OPERATION_SYMBOLS)
	{
		operandPos = str.find(elem.first);
		if (operandPos != string::npos)
		{
			operand = elem.second;
			break;
		}
	}
	if (operandPos == string::npos)
	{
		return false;
	}
	
	firstValue = str.substr(0, operandPos);
	secondValue = str.substr(operandPos + 1, str.size());
	return true;
}

void CCalculatorControl::PrintIdentifierValue(istream& args)
{
	string identifier;
	args >> identifier;
	if (m_calculator.HasIdentifier(identifier))
	{
		cout << setprecision(2) << fixed << m_calculator.GetIdentifierValue(identifier) << endl;
	}
	else
	{
		cout << "Identifier " << identifier << " does not exist" << endl;
	}
}

void CCalculatorControl::PrintVariables()
{
	for (auto it : m_calculator.GetVars())
	{
		cout << it.first << ":" << setprecision(2) << fixed << it.second << endl;
	}
}

void CCalculatorControl::PrintFunctions()
{
	for (auto it : m_calculator.GetFunctions())
	{
		cout << it.first << ":" << setprecision(2) << fixed << m_calculator.GetIdentifierValue(it.first) << endl;
	}
}