#include <iostream>
#include <string>
#include <cstdlib> 
#include <vector>
#include <algorithm>
#include <exception>

class CConvertor
{
public:

    CConvertor()
    {
        InitNumbers();
    }

    std::string convert(int from, int to, std::string number)
    {
        if (!IsValidNumber(number, from))
        {
            std::cout << "Number contains invalid characters or out of radix range";
            throw std::exception();
        }

        return "a";
    }

private:
    std::vector<char> numbers;

    void InitNumbers()
    {
        for (int i = 0; i < 10; i++)
        {
            numbers.push_back(i + '0');
        }
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            numbers.push_back(ch);
        }
    }

    int StringToInt(const std::string& str, int radix, bool& wasError)
    {
        if (radix <= 10)
        {
            return std::stoi(str);
        }
        else
        {

        }
        return 1;
    }

    std::string IntToString(int n, int radix, bool& wasError)
    {
        return "a";
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
    CConvertor convertor;

    try
    {
        convertor.convert(args.numberSystemFrom, args.numberSystemTo, args.number);
    }
    catch (const std::exception&)
    {
        return 1;
    };

    return 0;
}