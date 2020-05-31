#pragma once
#include <sstream>
#include <functional>
#include "CCalculator.h"

class CCalculatorControl
{
public:
	CCalculatorControl(CCalculator calculator, std::istream& input, std::ostream& output);
	bool ExecuteCommand();

private:
	void AddVar(std::istream& args);
	void SetVarValue(std::istream& args);
	void SetFunction(std::istream& args);
	void PrintIdentifierValue(std::istream& args);
	void PrintVariables();
	void PrintFunctions();
	bool ParseStrToValue(const std::string& str, std::string& firstValue, std::string& secondValue);
	bool ParseStrToAripthOperation(const std::string& str, std::string& firstValue, Operator& operand, std::string& secondValue);

	using ActionMap = std::map <std::string, std::function<void(std::istream & args)>>;
	std::istream& m_input;
	std::ostream& m_output;
	CCalculator m_calculator;
	const ActionMap m_actionMap;
};

