#include <map>
#include <vector>
#include <string>

const int SIGN_OF_LACK = -1;

struct BohrVertex
{
    std::map<char, int> adjacentVertexes;
    std::vector<int> autoMove;
    int suffLink = SIGN_OF_LACK;
    int parentVertex;
    char parentVertexSymbol;
    int lineNumber;
    bool isWord = false;
};

using BohrTree = std::vector<BohrVertex>;

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params);