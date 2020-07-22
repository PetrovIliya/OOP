#pragma once
#include "CCalculator.h"

using namespace std;

namespace
{
	bool IsCharCorrect(char ch)
	{
		return isalnum(ch) || ch == '_';
	}
}

bool FunctionData::empty()
{
	return firstOperand.empty() && secondOperand.empty();
}

//public

bool CCalculator::AddVar(const string& variable)
{
	if (!IsNameCorrect(variable) || IsFunctionExist(variable) || IsVarExist(variable))
	{
		return false;
	}
	m_variables.insert({ variable, numeric_limits<double>::quiet_NaN() });
	return true;
}

const map<string, double>& CCalculator::GetVars() const
{
	return m_variables;
}

bool CCalculator::SetVarValue(const string& varName, const string& value)
{
	if (value.empty() || IsFunctionExist(varName))
	{
		return false;
	}
	if (!IsVarExist(varName) && !AddVar(varName))
	{
		return false;
	}

	m_variables[varName] = IsVarExist(value) ? GetIdentifierValue(value) : stod(value);

	return true;
}

bool CCalculator::IsNameCorrect(const string& name) const
{
	if (name.empty() || isdigit(*name.begin()) || !all_of(name.begin(), name.end(), IsCharCorrect))
	{
		return false;
	}
	return true;
}

const map<string, FunctionData>& CCalculator::GetFunctions()
{
	return m_functions;
}

bool CCalculator::SetFunction(const string& functionName, const string& variable)
{
	if (HasIdentifier(functionName) || !IsNameCorrect(functionName) || !HasIdentifier(variable))
	{
		return false;
	}

	FunctionData functionData;
	functionData.firstOperand = variable;
	m_functions.insert(make_pair(functionName, functionData));

	return true;
}

bool CCalculator::SetFunction(const string& functionName, const string& varName1,
	Operator functionOperator, const string& varName2)
{
	if (HasIdentifier(functionName) || !IsNameCorrect(functionName) ||
		!HasIdentifier(varName1) || !HasIdentifier(varName2) ||
		functionOperator == Operator::None)
	{
		return false;
	}

	FunctionData functionData;
	functionData.firstOperand = varName1;
	functionData.secondOperand = varName2;
	functionData.operatorType = functionOperator;

	m_functions.insert({functionName, functionData});

	return true;
}

double CCalculator::GetIdentifierValue(const string& identifier)
{
	double value = numeric_limits<double>::quiet_NaN();
	if (IsFunctionExist(identifier))
	{
		value = CalculateFunction(identifier);
	}
	if (IsVarExist(identifier))
	{
		value = m_variables[identifier];
	}

	return value;
}

//private

double CCalculator::CalculateFunction(const string& functionName)
{
	if (!IsFunctionExist(functionName))
	{
		return numeric_limits<double>::quiet_NaN();
	}

	FunctionData functionData = m_functions[functionName];

	if (functionData.empty())
	{
		 return numeric_limits<double>::quiet_NaN();
	}

	string firstOperand = functionData.firstOperand;
	string secondOperand = functionData.secondOperand;

	if (secondOperand.empty())
	{
		return IsFunctionExist(firstOperand) ? CalculateFunction(firstOperand) : m_variables[firstOperand];
	}

	double firstOperandValue = IsFunctionExist(firstOperand) ? CalculateFunction(firstOperand) : m_variables[firstOperand];
	double secondOperandValue = IsFunctionExist(secondOperand) ? CalculateFunction(secondOperand) : m_variables[secondOperand];

	return GetArithmeticExpressionResult(firstOperandValue, secondOperandValue, functionData.operatorType);
}

double CCalculator::GetArithmeticExpressionResult(double leftArg, double rightArg, const Operator& operation)
{
	switch (operation)
	{
		case Operator::Plus:
			return leftArg + rightArg;
		case Operator::Division:
			return rightArg == 0 ? numeric_limits<double>::quiet_NaN() : leftArg / rightArg;
		case Operator::Multiplication:
			return leftArg * rightArg;
		case Operator::Minus:
			return leftArg - rightArg;
		default:
			return numeric_limits<double>::quiet_NaN();
	}
}

bool CCalculator::IsVarExist(const string& var) const
{
	return m_variables.find(var) != m_variables.end();
}

bool CCalculator::IsFunctionExist(const string& functionName) const
{
	return m_functions.find(functionName) != m_functions.end();
}

bool CCalculator::HasIdentifier(const std::string& id) const
{
	return IsFunctionExist(id) || IsVarExist(id);
}