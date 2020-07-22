#include <iostream>
#define CATCH_CONFIG_MAIN

#include "../../../catch2/catch.hpp"
#include "../Calculator/CCalculator.h"
#include "../Calculator/CCalculatorControl.h"


bool IsNan(const double& numeric)
{
	return numeric != numeric;
}

TEST_CASE("Add var")
{
	CCalculator calc;
	REQUIRE(calc.AddVar("x"));
	auto vars = calc.GetVars();
	REQUIRE(vars.find("x") != vars.end());
}
TEST_CASE("You cannot declare a variable twice")
{
	CCalculator calc;
	REQUIRE(calc.AddVar("x"));
	REQUIRE(!calc.AddVar("x"));
}
TEST_CASE("the value of an undeclared variable is NAN")
{
	CCalculator calc;
	REQUIRE(calc.GetVars().empty());
	REQUIRE(IsNan(calc.GetIdentifierValue("x")));
}

TEST_CASE("Variable can be set to")
{
	CCalculator calc;
	REQUIRE(calc.GetVars().empty());
	REQUIRE(IsNan(calc.GetIdentifierValue("x")));
	REQUIRE(calc.SetVarValue("x", "579"));
	REQUIRE(calc.GetIdentifierValue("x") ==  579);
}
TEST_CASE("variable cannot be set to empty value")
{
	CCalculator calc;
	REQUIRE(calc.GetVars().empty());
	REQUIRE(IsNan(calc.GetIdentifierValue("x")));
	REQUIRE(!calc.SetVarValue("x", ""));
}
TEST_CASE("you can set the value of the variable, if it can be determined")
{
	CCalculator calc;

	REQUIRE(calc.GetVars().empty());
	REQUIRE(!calc.SetVarValue("5x", "5"));
}
TEST_CASE("a variable can be passed the value of another variable")
{
	CCalculator calc;

	REQUIRE(calc.GetVars().empty());
	REQUIRE(IsNan(calc.GetIdentifierValue("x")));
	REQUIRE(calc.SetVarValue("x", "579"));
	REQUIRE(calc.SetVarValue("y", "x"));
	REQUIRE(calc.GetIdentifierValue("y") == 579);
}
TEST_CASE("variable name cannot start with a digit and be empty")
{
	CCalculator calc;

	REQUIRE(calc.GetVars().empty());
	REQUIRE(!calc.AddVar(""));
	REQUIRE(!calc.AddVar("12qww"));
}
TEST_CASE("you can declare a function with a previously undeclared identifier")
{
	CCalculator calc;

	REQUIRE(calc.GetFunctions().empty());
	REQUIRE(calc.SetVarValue("x", "5"));
	REQUIRE(calc.SetVarValue("y", "7"));
	REQUIRE(calc.SetFunction("f", "x", Operator::Plus, "y"));
	REQUIRE(IsNan(calc.GetIdentifierValue("fuction")));
}
TEST_CASE("function name cannot be empty")
{
	CCalculator calc;

	REQUIRE(calc.GetFunctions().empty());
	REQUIRE(calc.SetVarValue("x", "5"));
	REQUIRE(calc.SetVarValue("y", "7"));
	REQUIRE(!calc.SetFunction("", "x", Operator::Minus, "y"));
	REQUIRE(calc.GetFunctions().empty());
}
TEST_CASE("function name must be valid")
{
	CCalculator calc;

	REQUIRE(calc.GetFunctions().empty());
	REQUIRE(calc.SetVarValue("x", "5"));
	REQUIRE(calc.SetVarValue("y", "7"));
	REQUIRE(!calc.SetFunction("123z", "x", Operator::Minus, "y"));
	REQUIRE(!calc.SetFunction("123z", "x"));
	REQUIRE(!calc.SetFunction("z", "r"));
	REQUIRE(calc.GetFunctions().empty());
}

TEST_CASE("addition")
{
	CCalculator calc;
	calc.SetVarValue("x", "2");
	calc.SetVarValue("y", "3");
	REQUIRE(calc.SetFunction("f", "x", Operator::Plus, "y"));
	REQUIRE(calc.GetIdentifierValue("f") == 5);
}
TEST_CASE("subtraction")
{
	CCalculator calc;
	calc.SetVarValue("x", "2");
	calc.SetVarValue("y", "3");
	REQUIRE(calc.SetFunction("f", "x", Operator::Minus, "y"));
	REQUIRE(calc.GetIdentifierValue("f") == -1);
}
TEST_CASE("multiplication")
{
	CCalculator calc;
	calc.SetVarValue("x", "2");
	calc.SetVarValue("y", "3");
	REQUIRE(calc.SetFunction("f", "x", Operator::Multiplication, "y"));
	REQUIRE(calc.GetIdentifierValue("f") == 6);
}
TEST_CASE("division")
{
	CCalculator calc;
	calc.SetVarValue("x", "2");
	calc.SetVarValue("y", "3");
	REQUIRE(calc.SetFunction("f", "y", Operator::Division, "x"));
	REQUIRE(calc.GetIdentifierValue("f") == 1.5);
}
TEST_CASE("Сannot declare a function with an undeclared variable or invalid operators")
{
	CCalculator calc;
	calc.SetVarValue("x", "2");
	calc.SetVarValue("y", "3");
	REQUIRE(!calc.SetFunction("f", "z", Operator::Division, "x"));
	REQUIRE(!calc.SetFunction("f", "y", Operator::Division, "z"));
	REQUIRE(!calc.SetFunction("f", "x", Operator::None, "y"));
}


TEST_CASE("Can declare a function through another function")
{
	CCalculator calc;
	calc.SetVarValue("a", "2");
	calc.SetVarValue("b", "3");
	calc.SetVarValue("c", "4");
	REQUIRE(calc.SetFunction("f", "a", Operator::Plus, "b"));
	REQUIRE(calc.SetFunction("f1", "f"));
	REQUIRE(calc.GetIdentifierValue("f") == 5);
	REQUIRE(calc.SetFunction("g", "f", Operator::Plus, "c"));
	REQUIRE(calc.SetFunction("u", "f", Operator::Plus, "g"));
	REQUIRE(calc.GetIdentifierValue("u") == 14);
	REQUIRE(calc.SetVarValue("a", "100"));
	REQUIRE(calc.GetIdentifierValue("u") == 210);
}

TEST_CASE("fibonacci numbers")
{
	CCalculator calc;

	REQUIRE(calc.SetVarValue("v0", "0"));
	REQUIRE(calc.SetVarValue("v1", "1"));
	REQUIRE(calc.SetFunction("fib0", "v0"));
	REQUIRE(calc.SetFunction("fib1", "v1"));
	REQUIRE(calc.SetFunction("fib2", "fib1", Operator::Plus, "fib0"));
	REQUIRE(calc.SetFunction("fib3", "fib2", Operator::Plus, "fib1"));
	REQUIRE(calc.SetFunction("fib4", "fib3", Operator::Plus, "fib2"));
	REQUIRE(calc.SetFunction("fib5", "fib4", Operator::Plus, "fib3"));
	REQUIRE(calc.SetFunction("fib6", "fib5", Operator::Plus, "fib4"));
	REQUIRE(calc.GetIdentifierValue("fib0") == 0);
	REQUIRE(calc.GetIdentifierValue("fib1") == 1);
	REQUIRE(calc.GetIdentifierValue("fib2") == 1);
	REQUIRE(calc.GetIdentifierValue("fib3") == 2);
	REQUIRE(calc.GetIdentifierValue("fib4") == 3);
	REQUIRE(calc.GetIdentifierValue("fib5") == 5);
	REQUIRE(calc.GetIdentifierValue("fib6") == 8);
	REQUIRE(calc.SetVarValue("v0", "1"));
	REQUIRE(calc.GetIdentifierValue("fib0") == 1);
	REQUIRE(calc.GetIdentifierValue("fib1") == 1);
	REQUIRE(calc.GetIdentifierValue("fib2") == 2);
	REQUIRE(calc.GetIdentifierValue("fib3") == 3);
	REQUIRE(calc.GetIdentifierValue("fib4") == 5);
	REQUIRE(calc.GetIdentifierValue("fib5") == 8);
	REQUIRE(calc.GetIdentifierValue("fib6") == 13);
}