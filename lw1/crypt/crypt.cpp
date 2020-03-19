#include <iostream>
#include <string>
#include <exception>
#include <fstream>

using namespace std;

const string CRYPT_EXECUTION_MODE = "crypt";
const string DECRIPT_EXCECUTION_MODE = "decrypt";

enum ExecutionMode
{
    CRYPT,
    DECRYPT
};

struct Args
{
   string inputFileName;
   string outputFileName;
   ExecutionMode executionMode;
   int key;
};

bool IsNumeric(const std::string& string)
{
    for (const char ch : string)
    {
        if (!isdigit(ch))
        {
            return false;
        }
    }

    return true;
}

ExecutionMode GetExecutionMode(const std::string& modeName)
{
    std::string lowerCaseModeName = "";

    for (size_t i = 0; i < modeName.length(); i++)
    {
        lowerCaseModeName += tolower(modeName[i]);
    }

    if (lowerCaseModeName == CRYPT_EXECUTION_MODE)
    {
        return CRYPT;
    }
    else if (lowerCaseModeName == DECRIPT_EXCECUTION_MODE)
    {
        return DECRYPT;
    }
    else
    {
        throw std::invalid_argument("Invalid execution mode");
    }
}

Args ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        throw invalid_argument("Wrong quantity of parameters.\nUsage: crypt.exe <mode> <input file name> <output file name> <key>\n");
    }
    if (!IsNumeric(argv[4]))
    {
        throw invalid_argument("Key should be a number\n");
    }
    if (argv[2] == "" || argv[3] == "")
    {
        throw invalid_argument("input or output file name is empty\n");
    }

    Args args;
    args.inputFileName = argv[2];
    args.outputFileName = argv[3];
    args.key = stoi(argv[4]);
    args.executionMode = GetExecutionMode(argv[1]);

    if (args.key > 255 || args.key < 0)
    {
        throw invalid_argument("Key should be between 0 and 255");
    }

    return args;
}

void EncryptByte(char& byte, const int key)
{
    byte ^= key;

    byte = ((byte & 0b00000111) << 2)
        | ((byte & 0b00011000) << 3)
        | ((byte & 0b01100000) >> 5)
        | ((byte & 0b10000000) >> 2);
}

void DecryptByte(char& byte, const int key)
{
    byte = ((byte & 0b00000011) << 5)
        | ((byte & 0b00011100) >> 2)
        | ((byte & 0b00100000) << 2)
        | ((byte & 0b11000000) >> 3);

    byte ^= key;
}

void Transform(const string &inputFileName, const string &outputFileName, int key, const ExecutionMode& executionMode)
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

    char byte;
    while (inputFile.read(&byte, sizeof(char)))
    {
        (executionMode == CRYPT) ? EncryptByte(byte, key) : DecryptByte(byte, key);
        outputFile.write(&byte, sizeof(byte));
    }

    if (!outputFile.flush())
    {
        throw std::runtime_error("Failed to save data on disk\n");
    }
}

int main(int argc, char* argv[])
{
    Args args;
    try
    {
        args = ParseArgs(argc, argv);
        Transform(args.inputFileName, args.outputFileName, args.key, args.executionMode);
    }
    catch (const exception& e)
    {
        cout << e.what() << '\n';
        return 1;
    }
    cout << "Data tranfomed successfully";

    return 0;
}
