#include <sstream>
#include <iostream>
#include "ExpandTemplate.h"

using namespace std;

void addNewBohrVertex(BohrTree& bohrTree, int lineNumber, int parentVertex, char parentVertexSymbol)
{
	BohrVertex bohrVertex;
	bohrVertex.lineNumber = lineNumber;
	bohrVertex.parentVertex = parentVertex;
	bohrVertex.parentVertexSymbol = parentVertexSymbol;
	bohrTree.push_back(bohrVertex);
}

void AddWordToBohrTree(BohrTree& bohrTree, string word)
{
	int currVertex = 0;
	int nextLineNumber;
	for (char ch : word)
	{
		if (bohrTree[currVertex].adjacentVertexes.find(ch) == bohrTree[currVertex].adjacentVertexes.end())
		{
			nextLineNumber = bohrTree[currVertex].lineNumber + 1;
			bohrTree[currVertex].adjacentVertexes[ch] = (int)bohrTree.size();
			addNewBohrVertex(bohrTree, nextLineNumber, currVertex, ch);
			currVertex = (int)bohrTree.size() - 1;
		}
		else
		{
			currVertex = bohrTree[currVertex].adjacentVertexes[ch];
		}
	}
	bohrTree[currVertex].isWord = true;
}

BohrTree GetBohrTree(const string const& tpl)
{
	BohrVertex bohrVertex;
	bohrVertex.lineNumber = 0;

	stringstream tplStream(tpl);
	string word;
	BohrTree bohrTree;
	bohrTree.push_back(bohrVertex);

	while (tplStream >> word)
	{
		AddWordToBohrTree(bohrTree, word);
	}

	return bohrTree;
}

string ExpandTemplate(string const& tpl, map<string, string> const& params)
{
	BohrTree bohrTree = GetBohrTree(tpl);


	return "";
}