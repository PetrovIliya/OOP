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


std::string ToUpperCase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), ::toupper);
    return string;
}

void CheckNumberForCorrectRadixRange(std::string number, int radix)
{
    if (number.empty())
    {
        throw std::invalid_argument("Number is empty");
    }
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
            throw std::invalid_argument("Number contains out of radix range symbols\n");
        }
    }
}

bool IsPositiveSummOverflowed(int arg1, int arg2)
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

unsigned int StringToInt(const std::string& str, int radixFrom, bool isConversionNumberNegative)
{
    if (str.empty())
    {
        throw std::invalid_argument("An error occurred during program execution\n");
    }
    CheckNumberForCorrectRadixRange(str, radixFrom);
    std::vector<char>::const_iterator it;
    unsigned int result = 0;
    unsigned int tmpResult;
    int intNumber;
    for (char ch : str)
    {
        it = std::find(possibleNumbersOfNumberSystem.begin(), possibleNumbersOfNumberSystem.end(), ch);
        intNumber = (int)std::distance(possibleNumbersOfNumberSystem.begin(), it);

        tmpResult = result;
        if (isConversionNumberNegative && tmpResult != 0)
        {
            tmpResult--;
        }
        if (IsMultOverflowed(radixFrom, tmpResult))
        {
            throw std::overflow_error("Overflow detected");
        }
        int multResult = radixFrom * result;
        if (isConversionNumberNegative && multResult != 0)
        {
            multResult--;
        }
        if (IsPositiveSummOverflowed(multResult, intNumber))
        {
            throw std::overflow_error("Overflow detected");
        }

        result = (result * radixFrom) + intNumber;
    }
    return result;
}

std::string IntToString(unsigned int number, int radixTo)
{

    if (radixTo == 0)
    {
        throw std::invalid_argument("Radix can't be zero\n");
    }

    std::vector<unsigned int> remindersOfDivision;
    std::string result;

    while (number >= (unsigned)radixTo)
    {
        remindersOfDivision.push_back(possibleNumbersOfNumberSystem[number % radixTo]);
        number /= radixTo;

    }
    remindersOfDivision.push_back(possibleNumbersOfNumberSystem[number]);
    for (int i = (int)remindersOfDivision.size() - 1; i >= 0; i--)
    {
        result += remindersOfDivision[i];
    }

    return result;
}


std::string Convert(int from, int to, std::string number)
{
    if (number.empty())
    {
        throw std::invalid_argument("Number is empty");
    }
    bool isConversionNumberNegative = false; 
    if (number[0] == '-')
    {
        number.erase(0, 1);
        isConversionNumberNegative = true;
    }
    unsigned int intNumber = StringToInt(number, from, isConversionNumberNegative);
    std::string result = IntToString(intNumber, to);
    if (isConversionNumberNegative && result != "0")
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

bool IsNumberBetween(int number, int from, int to)
{
    if (number < from || number > to)
    {
        return false;
    }

    return true;
}

Args ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        throw  std::runtime_error("Wrong quantity of parameters.\nUsage: radix.exe <numeral system from> <number system to> <number>\n");
    }

    if (!IsNumeric(argv[1]) || !IsNumeric(argv[2]))
    {
        throw  std::invalid_argument("Wrong numeral system. Numeral system should be a decimal number\n");
    }

    Args args;
    args.numeralSystemFrom = atoi(argv[1]);
    args.numeralSystemTo = atoi(argv[2]);
    args.number = ToUpperCase(argv[3]);

    if (!IsNumberBetween(args.numeralSystemFrom, 2, 36) || !IsNumberBetween(args.numeralSystemTo, 2, 36))
    {
        throw  std::invalid_argument("Wrong numeral system. Numeral system should be between 2 and 36\n");
    }
   
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
    catch (std::invalid_argument & e)
    {
        std::cout << e.what() << '\n';
        return 1;
    }
    catch (std::runtime_error & e)
    {
        std::cout << e.what() << '\n';
        return 1;
    }
    return 0;
}