#include <iostream>
#include <string>
#include <cstdlib> 
#include <vector>
#include <algorithm>
#include <exception>

class CNumberSystemConvertor
{
public:

    CNumberSystemConvertor()
    {
        InitNumbers();
    }

    std::string convert(int from, int to, std::string number)
    {
        toUpperCase(number);
        CheckNumberSystem(from, to);
        CheckInput(number, from);
        DeleteFirstSymbolIfNegative(number);
        std::cout << number << std::endl;
        int decNumber = StringToInt(number, from);
        std::string result = IntToString(decNumber, to);

        return result;
    }

private:
    std::vector<char> numbers;
    bool isNegative = false;

    void DeleteFirstSymbolIfNegative(std::string &str)
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

    int StringToInt(const std::string& str, int radix)
    {
        int stringLength = str.size();
        if (stringLength == 0)
        {
            throw std::exception("Emptmy number\n");
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

    std::string IntToString(int n, int radix)
    {
        char str[30] = "\0";
        int errCode;

        errCode = _itoa_s(n, str, radix);
        
        if (errCode != 0)
        {
            throw std::exception("An error occurred while converting\n");
        }

        return str;
    }

    void CheckInput(const std::string& str, int radix)
    {
        std::vector<char>::iterator it;
        int position;
        char firstSymbol = str[0];
        if (firstSymbol == '-')
        {
            isNegative = true;
        }
        for (char ch : str)
        {
            it = std::find(numbers.begin(), numbers.end(), ch);
            if (it == numbers.end() && !isNegative)
            {
                throw std::exception("Number contains wrong symbols\n");
            }
            position = std::distance(numbers.begin(), it);
            if (position >= radix && !isNegative)
            {
                throw std::exception("Number contains out of radix range symbols\n");
            }
        }
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
    CNumberSystemConvertor convertor;

    try
    {
        std::string result = convertor.convert(args.numberSystemFrom, args.numberSystemTo, args.number);
        std::cout << result << std::endl;
    }
    catch(const std::exception & e)
    {
        std::cout << e.what() << '\n';
        return 1;
    };


    return 0;
}