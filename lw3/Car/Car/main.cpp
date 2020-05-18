#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include "Car.h"
#include "StringUtilities.h"

using namespace std;

struct Command
{
    string action;
    int argument;
};

map <string, string> listOfCommands = {
    {"Info", "Shows car info"},
    {"EngineOn", "Turn engine on"},
    {"EngineOff", "Turn engine off"},
    {"SetGear <gear>", "Set gear from -1 to 5"},
    {"SetSpeed <speed>", "Set speed of car"},
    {"Exit", "Close programm"}
};

vector <string> possibleCommands = {"info", "engineon", "engineoff", "setgear", "setspeed", "exit", "help"};

bool NeedArgument(string const& action)
{
    return (action == "setgear") || (action == "setspeed");
}

bool ParseCommand(Command& command)
{
    cout << "> ";
    string userInput;
    getline(cin, userInput);

    istringstream input(userInput);

    input >> command.action;
    ToLower(command.action);

    if (find(possibleCommands.begin(), possibleCommands.end(), command.action) == possibleCommands.end())
    {
        return false;
    }

    if (NeedArgument(command.action) && !(input >> command.argument))
    {
        return false;
    }

    return true;
}

bool ReadCommand(Command& command)
{
    while (!ParseCommand(command))
    {
        cout << "Wrong command. To see list of commands type Help" << endl;
    }

    return command.action != "exit";
}

void ExecuteHelp()
{
    for (pair<string, string> command : listOfCommands)
    {
        cout << command.first << ": " << command.second << endl;
    }
}

void ExecuteInfo(CCar& car, const int argument)
{
    cout << "Car Info" << endl;
    cout << "Gear: " << car.GetGear() << endl;
    cout << "Speed: " << car.GetSpeed() << endl;
    cout << "Direction: ";

    switch (car.GetDirection())
    {
    case CCar::Direction::Ahead:
    {
        cout << "Ahead";
        break;
    }
    case CCar::Direction::Back:
    {
        cout << "Back";
        break;
    }
    case CCar::Direction::None:
    {
        cout << "None";
        break;
    }
    }
    cout << endl;
}

void ExecuteSetSpeed(CCar& car, const int argument)
{
    if (car.SetSpeed(argument))
    {
        cout << "New speed: " << argument << endl;
    }
    else
    {
        cout << "Can't set speed" << endl;
    }
}

void ExecuteSetGear(CCar& car, const int argument)
{
    if (car.SetGear(argument))
    {
        cout << "New gear: " << argument << endl;
    }
    else
    {
        cout << "Can't set gear" << endl;
    }
}

void ExecuteEngineOn(CCar& car)
{
    if (car.TurnOnEngine())
    {
        cout << "Engine started!" << endl;
    }
    else
    {
        cout << "Engine is already working" << endl;
    }
}

void ExecuteEngineOff(CCar& car)
{
    if (car.TurnOffEngine())
    {
        cout << "Engine stoped!" << endl;
    }
    else
    {
        cout << "Can't stop engine now" << endl;
    }
}

void ExecuteCommand(Command const& command, CCar& car)
{
    if (command.action == "help")
    {
        ExecuteHelp();
    }
    else if (command.action == "info")
    {
        ExecuteInfo(car, command.argument);
    }
    else if (command.action == "engineon")
    {
        ExecuteEngineOn(car);
    }
    else if (command.action == "engineoff")
    {
        ExecuteEngineOff(car);
    }
    else if (command.action == "setgear")
    {
        ExecuteSetGear(car, command.argument);
    }
    else if (command.action == "setspeed")
    {
        ExecuteSetSpeed(car, command.argument);
    }
}

int main(int argc, char* argv[])
{  
    cout << "Hello! Enter command or type Help to see list of commands" << endl;
    Command command;
    CCar car;

    while (ReadCommand(command))
    {
        ExecuteCommand(command, car);
    }


    return 0;
}