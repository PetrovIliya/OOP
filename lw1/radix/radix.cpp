#include <iostream>
#include <string>
#include <cstdlib> 
#include <vector>
#include <algorithm>

struct ErrorCodes
{
    static const int WRONG_SYMBOLS_ERR = 1;
    static const int NO_NUMBER_ERR = 2;
    static const int CONVERT_ERROR = 3;
};

class CConvertor
{
public:

    CConvertor()
    {
        InitNumbers();
    }

    std::string convert(int from, int to, std::string number, bool &wasError)
    {
        toUpperCase(number);
        if (!IsValidNumber(number, from))
        {
            errorCode = ErrorCodes::WRONG_SYMBOLS_ERR;
            wasError = true;
            return "";
        }
        int decNumber = StringToInt(number, from, wasError);

        if (wasError)
        {
            return "";
        }
        std::string result = IntToString(decNumber, to, wasError);

        if (wasError)
        {
            return "";
        }
        return result;
    }

    void PrintError()
    {
        std::cout << "test";
        switch (errorCode)
        {
            case ErrorCodes::WRONG_SYMBOLS_ERR:
                std::cout << "Number Contains wrong symbols or symbols out of radix range\n";
                break;
            case ErrorCodes::NO_NUMBER_ERR:
                std::cout << "Emptmy number\n";
                break;
            case ErrorCodes::CONVERT_ERROR:
                std::cout << "An error occurred while converting\n";
                break;
        }
    }

private:
    std::vector<char> numbers;
    int errorCode = 0;

    void InitNumbers()
    {
        for (int i = 0; i < 10; i++)
        {
            numbers.push_back(i + '0');
        }
        for (char ch = 'A'; ch <= 'Z'; ch++)
        {
            numbers.push_back(ch);
        }
    }

    void toUpperCase(std::string& string)
    {
        std::transform(string.begin(), string.end(), string.begin(), ::toupper);
    }

    int StringToInt(const std::string& str, int radix, bool& wasError)
    {
        int stringLength = str.size();
        if (stringLength == 0)
        {
            wasError = true;
            errorCode = ErrorCodes::NO_NUMBER_ERR;
            return -1;
        }
        if (radix == 10)
        {
            return std::stoi(str);
        }

        return ConvertToDec(str, stringLength, radix);
    }

    int ConvertToDec(std::string str, int stringLength, int radix)
    {
        std::vector <int> intNumbers = GetNumericList(str);
        int basis = 0;
        int result = 0;
        for (int i = stringLength - 1; i >= 0; i--)
        {
            result += intNumbers[i] * pow(radix, basis);
            if (basis == 0)
            {
                basis = 1;
            }
            else
            {
                basis <<= 1;
            }
        }

        return result;
    }

    std::vector <int> GetNumericList(std::string str)
    {
        std::vector<char>::iterator it;
        std::vector <int> intNumbers;
        int position;
        for (char ch : str)
        {
            it = std::find(numbers.begin(), numbers.end(), ch);
            position = std::distance(numbers.begin(), it);
            intNumbers.push_back(position);
        }

        return intNumbers;
    }

    std::string IntToString(int n, int radix, bool& wasError)
    {
        char str[30];
        int errCode;

        errCode = _itoa_s(n, str, radix);
        
        if (errCode != 0)
        {
            wasError = true;
            errorCode = ErrorCodes::CONVERT_ERROR;
            return "";
        }

        return str;
    }

    bool IsValidNumber(const std::string& str, int radix)
    {
        std::vector<char>::iterator it;
        int position;
        for (char ch : str)
        {
            it = std::find(numbers.begin(), numbers.end(), ch);
            if (it == numbers.end())
            {
                return false;
            }
            position = std::distance(numbers.begin(), it);
            if (position >= radix)
            {
                return false;
            }
        }

        return true;
    }
};

struct Args
{
    int numberSystemFrom;
    int numberSystemTo;
    std::string number;
};


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
    bool wasError = false;
    CConvertor convertor;
    std::string result = convertor.convert(args.numberSystemFrom, args.numberSystemTo, args.number, wasError);
    if (wasError)
    {
        convertor.PrintError();
        return 1;
    }

    std::cout << result << std::endl;

    return 0;
}