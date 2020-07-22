#pragma once
#include "stdafx.h"

enum class Operator
{
	Plus,
	Minus,
	Multiplication,
	Division,
	None
};

struct FunctionData
{
	std::string firstOperand;
	std::string secondOperand;
	Operator operatorType = Operator::None;
	bool empty();
};

static const std::map<std::string, Operator> OPERATION_SYMBOLS
{
	{ "+", Operator::Plus },
	{ "-", Operator::Minus },
	{ "*", Operator::Multiplication },
	{ "/", Operator::Division }
};

class CCalculator
{
public:
	CCalculator() = default;
	~CCalculator() = default;

	bool AddVar(const std::string& variable);
	const std::map<std::string, double>& GetVars() const;
	bool SetVarValue(const std::string& lhs, const std::string& rhs);
	const std::map<std::string, FunctionData>& GetFunctions();
	bool SetFunction(const std::string& functionName, const std::string& variable);
	bool SetFunction(const std::string& functionName, const std::string& firstIdentifier,
		Operator operatorFunction, const std::string& secondIdentifier);
	bool HasIdentifier(const std::string& id) const;
	double GetIdentifierValue(const std::string& identifier);

private:
	double CalculateFunction(const std::string& functionName);
	double GetArithmeticExpressionResult(double leftArg, double rightArg, const Operator& operation);
	bool IsNameCorrect(const std::string& id) const;
	bool IsFunctionExist(const std::string& nameFunction) const;
	bool IsVarExist(const std::string& variable) const;

	std::map<std::string, FunctionData> m_functions;
	std::map<std::string, double> m_variables;
};