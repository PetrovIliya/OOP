#include <sstream>
#include <iostream>
#include "ExpandTemplate.h"

using namespace std;

int GetAutoMove(BohrTree& bohrTree, int vertex, char ch);

int GetSuffLink(BohrTree& bohrTree, int vertex)
{
	if (bohrTree[vertex].suffLink == SIGN_OF_LACK)
	{
		if (vertex == BOHR_TREE_ROOT || bohrTree[vertex].parentVertex == BOHR_TREE_ROOT)
		{
			bohrTree[vertex].suffLink = BOHR_TREE_ROOT;
		}
		else
		{
			int suffLink = GetSuffLink(bohrTree, bohrTree[vertex].parentVertex);
			char parentVertexSymbol = bohrTree[vertex].parentVertexSymbol;
			bohrTree[vertex].suffLink = GetAutoMove(bohrTree, suffLink, parentVertexSymbol);
		}
	}

	return bohrTree[vertex].suffLink;

}

int GetAutoMove(BohrTree& bohrTree, int vertex, char ch)
{
	if (bohrTree[vertex].autoMove.find(ch) == bohrTree[vertex].autoMove.end())
	{
		if (bohrTree[vertex].adjacentVertexes.find(ch) != bohrTree[vertex].adjacentVertexes.end())
		{
			bohrTree[vertex].autoMove[ch] = bohrTree[vertex].adjacentVertexes[ch];
		}
		else
		{
			if (vertex == 0)
			{
				bohrTree[vertex].autoMove[ch] = 0;
			}
			else
			{
				int suffLink = GetSuffLink(bohrTree, vertex);
				bohrTree[vertex].autoMove[ch] = GetAutoMove(bohrTree, suffLink, ch);
			}
		}
	}


	return bohrTree[vertex].autoMove[ch];
}

int GetGoodSuffLink(BohrTree& bohrTree, int v)
{
	if (bohrTree[v].goodSuffLink == SIGN_OF_LACK)
	{
		int u = GetSuffLink(bohrTree, v);
		if (u == BOHR_TREE_ROOT)
		{
			bohrTree[v].goodSuffLink = BOHR_TREE_ROOT;
		}
		else
		{
			bohrTree[v].goodSuffLink = (bohrTree[u].isWord) ? u : GetGoodSuffLink(bohrTree, u);
		}
	}

	return bohrTree[v].goodSuffLink;

}

void AddNewBohrVertex(BohrTree& bohrTree, int parentVertex, char parentVertexSymbol)
{
	BohrVertex bohrVertex;
	bohrVertex.parentVertex = parentVertex;
	bohrVertex.parentVertexSymbol = parentVertexSymbol;
	bohrTree.push_back(bohrVertex);
}

void AddWordToBohrTree(BohrTree& bohrTree, string word, int patternIndex)
{
	int currVertex = 0;
	for (char ch : word)
	{
		if (bohrTree[currVertex].adjacentVertexes.find(ch) == bohrTree[currVertex].adjacentVertexes.end())
		{
			bohrTree[currVertex].adjacentVertexes[ch] = (int)bohrTree.size();
			AddNewBohrVertex(bohrTree, currVertex, ch);
			currVertex = (int)bohrTree.size() - 1;
		}
		else
		{
			currVertex = bohrTree[currVertex].adjacentVertexes[ch];
		}
	}
	bohrTree[currVertex].isWord = true;
	bohrTree[currVertex].patternIndex = patternIndex;
}

BohrTree GetBohrTree(const vector<string>& pattern)
{
	BohrVertex bohrVertex;

	BohrTree bohrTree;
	bohrTree.push_back(bohrVertex);

	for (int i = 0; i < pattern.size(); i++)
	{
		AddWordToBohrTree(bohrTree, pattern[i], i);
	}

	return bohrTree;
}

vector<string> GetWordsForReplace(map<string, string> const& params)
{
	vector<string> wordsForReplace;

	for (pair<string, string> element : params)
	{
		wordsForReplace.push_back(element.first);
	}

	return wordsForReplace;
}

void check(BohrTree& bohrTree, int v, int i, const vector<string> & pattern)
{
	for (int u = v; u != 0; u = GetGoodSuffLink(bohrTree, u)) 
	{
		if (bohrTree[u].isWord) 
			cout << i - pattern[bohrTree[u].patternIndex].length() + 1 << " " << pattern[bohrTree[u].patternIndex] << endl;
	}
}

void find_all_pos(BohrTree& bohrTree, const string& s, const vector<string>& pattern)
{
	int u = 0;
	for (int i = 0; i < s.length(); i++) 
	{
		u = GetAutoMove(bohrTree, u, s[i]);

		check(bohrTree, u, i + 1, pattern);
	}
}

string ExpandTemplate(string const& tpl, map<string, string> const& params)
{
	vector<string> wordsForReplace = GetWordsForReplace(params);
	BohrTree bohrTree = GetBohrTree(wordsForReplace);

	find_all_pos(bohrTree, tpl, wordsForReplace);

	return "";
}