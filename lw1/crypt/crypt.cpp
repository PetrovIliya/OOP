#include <iostream>
#include <string>
#include <exception>
#include <fstream>

using namespace std;

const std::string templateOfNumbers = "0123456789";

struct Args
{
   string inputFileName;
   string outputFileName;
   int key;
};

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
        throw invalid_argument("Wrong quantity of parameters.\nUsage: crypt.exe <input file name> <output file name> <key>\n");
    }
    if (!IsNumeric(argv[3]))
    {
        throw invalid_argument("Key should be a number\n");
    }
    if (argv[1] == "" || argv[2] == "")
    {
        throw invalid_argument("input or output file name is empty\n");
    }

    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.key = stoi(argv[3]);

    if (args.key > 255 || args.key < 0)
    {
        throw invalid_argument("Key should be between 0 and 255");
    }

    return args;
}

void Crypt(const string &inputFileName, const string &outputFileName, int key)
{
    ifstream inputFile(inputFileName, ios::binary);
    if (!inputFile.is_open())
    {
        throw invalid_argument("Can\'t open input file");
    }
    ofstream outputFile(outputFileName, ios::binary);
    if (!outputFile.is_open())
    {
        throw invalid_argument("Can\'t open output file");
    }
    size_t count[256];
    std::fill_n(count, 256, 0);

    for (char c; inputFile.get(c); ++count[uint8_t(c)]);

    for (size_t i = 0; i < 256; ++i)
    {
        if (count[i] && isgraph(i)) // non-zero counts of printable characters
        {
            std::cout << char(i) << " = " << count[i] << '\n';
        }
    }
    
}

int main(int argc, char* argv[])
{
    Args args;
    try
    {
        args = ParseArgs(argc, argv);
        Crypt(args.inputFileName, args.outputFileName, args.key);
    }
    catch (const std::exception& e)
    {
        cout << e.what() << '\n';
    }
}
