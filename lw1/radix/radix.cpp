#include <iostream>
#include <string>
#include <cstdlib> 
#include <vector>
#include <algorithm>
#include <exception>


struct Args
{
    int numberSystemFrom = 0;
    int numberSystemTo = 0;
    std::string number = "";
};

void DeleteFirstSymbolIfNegative(std::string& str, bool isNegative)
{
    if (isNegative)
    {
        str.erase(0, 1);
    }
}

void CheckNumberSystem(int from, int to)
{
    if (from < 2 || to < 2)
    {
        throw std::exception("Wrong number system \n");
    }
}

void InitPossibleNumbersOfNumberSystem(std::vector<char> &possibleNumbersOfNumberSystem)
{
    for (int i = 0; i < 10; i++)
    {
        possibleNumbersOfNumberSystem.push_back(i + '0');
    }
    for (char ch = 'A'; ch <= 'Z'; ch++)
    {
        possibleNumbersOfNumberSystem.push_back(ch);
    }
}

void toUpperCase(std::string& string)
{
    std::transform(string.begin(), string.end(), string.begin(), ::toupper);
}

std::vector <int> GetDecimalNumberList(std::string str, std::vector<char> possibleNumbersOfNumberSystem)
{
    std::vector<char>::iterator it;
    std::vector <int> intNumbers;
    int position;
    for (char ch : str)
    {
        it = std::find(possibleNumbersOfNumberSystem.begin(), possibleNumbersOfNumberSystem.end(), ch);
        position = (int)std::distance(possibleNumbersOfNumberSystem.begin(), it);
        intNumbers.push_back(position);
    }

    return intNumbers;
}

int ConvertToDec(std::string str, int stringLength, int radix, std::vector<char> possibleNumbersOfNumberSystem)
{
    std::vector <int> decimalNumberList = GetDecimalNumberList(str, possibleNumbersOfNumberSystem);

    int numberRank = 0;
    int result = 0;

    for (int i = stringLength - 1; i >= 0; i--)
    {
        result += decimalNumberList[i] * (int)pow(radix, numberRank);
        numberRank++;
    }

    return result;
}

int StringToInt(const std::string& str, int radix, std::vector<char> possibleNumbersOfNumberSystem)
{
    int stringLength = (int)str.size();
    if (stringLength == 0)
    {
        throw std::exception("Emptmy number\n");
    }
    if (radix == 10)
    {
        return std::stoi(str);
    }

    return ConvertToDec(str, stringLength, radix, possibleNumbersOfNumberSystem);
}

std::string IntToString(int n, int radix)
{
    char str[11] = "\0";
    int errCode;

    errCode = _itoa_s(n, str, radix);

    if (errCode != 0)
    {
        throw std::exception("An error occurred while converting\n");
    }

    return str;
}

void checkSymbol(char symbol, std::vector<char> possibleNumbersOfNumberSystem, int radix)
{
    std::vector<char>::iterator it;
    it = std::find(possibleNumbersOfNumberSystem.begin(), possibleNumbersOfNumberSystem.end(), symbol);
    if (it == possibleNumbersOfNumberSystem.end())
    {
        throw std::exception("Number contains wrong symbols\n");
    }
    int position = (int)std::distance(possibleNumbersOfNumberSystem.begin(), it);
    if (position >= radix)
    {
        throw std::exception("Number contains out of radix range symbols\n");
    }
}

void CheckInput(const std::string& str, int radix, bool &isNegative, std::vector<char> possibleNumbersOfNumberSystem)
{
    char firstSymbol = str[0];
    if (firstSymbol == '-')
    {
        isNegative = true;
    }
    else
    {
        checkSymbol(firstSymbol, possibleNumbersOfNumberSystem, radix);
    }

    for (int i = 1; i < str.size(); i++)
    {
        checkSymbol(str[i], possibleNumbersOfNumberSystem, radix);
    }
}

std::string convert(int from, int to, std::string number)
{
    bool isNegative = false;
    std::vector<char> possibleNumbersOfNumberSystem;
    InitPossibleNumbersOfNumberSystem(possibleNumbersOfNumberSystem);
    toUpperCase(number);
    CheckNumberSystem(from, to);
    CheckInput(number, from, isNegative, possibleNumbersOfNumberSystem);
    DeleteFirstSymbolIfNegative(number, isNegative);
    int decNumber = StringToInt(number, from, possibleNumbersOfNumberSystem);

    std::string result = IntToString(decNumber, to);
    if (isNegative)
    {
        result.insert(0, 1, '-');
    }

    return result;
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "wrong quantity of parameters.\nUsage: radix.exe <number system from> <number system to> <number>";
    }
    Args args;
    args.numberSystemFrom = atoi(argv[1]);
    args.numberSystemTo = atoi(argv[2]);
    args.number = argv[3];

    try
    {
        std::string result = convert(args.numberSystemFrom, args.numberSystemTo, args.number);
        std::cout << result << std::endl;
    }
    catch(const std::exception & e)
    {
        std::cout << e.what() << '\n';
    };

    return 0;
}