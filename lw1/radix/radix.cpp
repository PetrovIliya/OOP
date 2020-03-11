#include <iostream>
#include <string>
#include <cstdlib> 
#include <vector>
#include <algorithm>
#include <exception>
#include <optional>

const std::string templateOfNumbers = "0123456789";
const std::vector<char> possibleNumbersOfNumberSystem = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                                        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

struct Args
{
    int numeralSystemFrom = 0;
    int numeralSystemTo = 0;
    std::string number;
};

void CheckNumberForEmptiness(std::string number)
{
    if (number.size() == 0)
    {
        throw std::exception("Number is empty\n");
    }
}

std::string ToUpperCase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), ::toupper);
    return string;
}

bool IsSummOverflowed(int arg1, int arg2)
{
    if (INT_MAX - arg1 - arg2 < 0)
    {
        return true;
    }

    return false;
}

bool IsMultOverflowed(int arg1, int arg2)
{
    if (arg1 == 0 && arg2 == 0)
    {
        return false;
    }
    int numberForDivision = arg2;
    int numberForComparison = arg1;
    if (numberForDivision == 0)
    {
        numberForDivision = arg1;
        numberForComparison = arg2;
    }
    if (numberForComparison > INT_MAX / numberForDivision)
    {
        return true;
    }

    return false;
}

void OverflowControl(int radix, unsigned int oldResult, int iterableNumber, bool isConversionNumberNegative)
{
    unsigned int tmpResult = oldResult;
    if (isConversionNumberNegative && tmpResult != 0)
    {
        tmpResult--;
    }
    if (IsMultOverflowed(radix, tmpResult))
    {
        throw std::exception("Overflow detected");
    }
    int multResult = radix * oldResult;
    if (isConversionNumberNegative)
    {
        multResult--;
    }
    if (IsSummOverflowed(multResult, iterableNumber))
    {
        throw std::exception("Overflow detected");
    }
}

unsigned int StringToInt(const std::string& str, int radix, bool isConversionNumberNegative)
{
    if (str.size() == 0)
    {
        throw std::exception("An error occurred during program execution\n");
    }
    if (radix == 10)
    {
        return std::stoi(str);
    }
    std::vector<char>::const_iterator it;
    unsigned int result = 0;
    int intNumber;
    for (char ch : str)
    {
        it = std::find(possibleNumbersOfNumberSystem.begin(), possibleNumbersOfNumberSystem.end(), ch);
        intNumber = (int)std::distance(possibleNumbersOfNumberSystem.begin(), it);
        OverflowControl(radix, result, intNumber, isConversionNumberNegative);
        result = (result * radix) + intNumber;
    }
    return result;
}

std::string IntToString(unsigned int number, int radix)
{
    if (radix == 0)
    {
        throw std::exception("Radix can't be zero\n");
    }
    if (radix == 10)
    {
        return std::to_string(number) ;
    }
    std::vector<unsigned int> remindersOfDivision;
    std::string result;
    while ((int)number >= radix)
    {
        remindersOfDivision.push_back(number % radix);
        number /= radix;
    }
    remindersOfDivision.push_back(number);
    for (size_t i = remindersOfDivision.size() - 1; i >= 0; i--)
    {
        result += std::to_string(remindersOfDivision[i]);
    }

    return result;
}

void CheckNumberForCorrectRadixRange(std::string number, int radix)
{
    CheckNumberForEmptiness(number);
    char firstSymbol = number[0];
    if (firstSymbol == '-')
    {
        number.erase(0, 1);
    }
    for (char symbol : number)
    {
        std::vector<char>::const_iterator it;
        it = std::find(possibleNumbersOfNumberSystem.begin(), possibleNumbersOfNumberSystem.end(), symbol);
        int position = (int)std::distance(possibleNumbersOfNumberSystem.begin(), it);
        if (it == possibleNumbersOfNumberSystem.end() || position >= radix)
        {
            throw std::exception("Number contains out of radix range symbols\n");
        }
    }
}

std::string Convert(int from, int to, std::string number)
{
    CheckNumberForEmptiness(number);
    bool isConversionNumberNegative = false; 
    if (number[0] == '-')
    {
        number.erase(0, 1);
        isConversionNumberNegative = true;
    }
    unsigned int intNumber = StringToInt(number, from, isConversionNumberNegative);
    std::string result = IntToString(intNumber, to);
    if (isConversionNumberNegative)
    {
        result.insert(0, 1, '-');
    }
    return result;
}

bool IsNumeric(const std::string& string)
{
    size_t offset = 0;
    if (string[offset] == '-')
    {
        ++offset;
    }
    return string.find_first_not_of(templateOfNumbers, offset) == std::string::npos;
}

Args ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
       throw  std::exception("Wrong quantity of parameters.\nUsage: radix.exe <numeral system from> <number system to> <number>\n");
    }
    if (!IsNumeric(argv[1]) || !IsNumeric(argv[2]) || atoi(argv[1]) < 2 || atoi(argv[2]) < 2 || atoi(argv[1]) > 36 || atoi(argv[2]) > 36)
    {
        throw  std::exception("Wrong numeral system. Numeral system should be between 2 and 36\n");
    }
    Args args;
    args.numeralSystemFrom = atoi(argv[1]);
    args.numeralSystemTo = atoi(argv[2]);
    args.number = ToUpperCase(argv[3]);
    CheckNumberForCorrectRadixRange(args.number, args.numeralSystemFrom);
    return args;
}

int main(int argc, char* argv[])
{
    Args args;
    try
    {
        args = ParseArgs(argc, argv);
        std::string result = Convert(args.numeralSystemFrom, args.numeralSystemTo, args.number);
        std::cout << result << std::endl;
    }
    catch(const std::exception & e)
    {
        std::cout << e.what() << '\n';
    };
    return 0;
}