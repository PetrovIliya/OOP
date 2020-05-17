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

void AddPosotionIfWord(BohrTree& bohrTree, int suffLinkVertex, int position, const vector<string>& pattern, map<int, string>& wordsPositions)
{
	for (int goodSuffLinkVertex = suffLinkVertex; goodSuffLinkVertex != 0; goodSuffLinkVertex = GetGoodSuffLink(bohrTree, goodSuffLinkVertex))
	{
		if (bohrTree[goodSuffLinkVertex].isWord)
		{
			int wordPositionInTemplate = position - (int)pattern[bohrTree[goodSuffLinkVertex].patternIndex].length();
			string word = pattern[bohrTree[goodSuffLinkVertex].patternIndex];
			wordsPositions[wordPositionInTemplate] = word;
		}
	}
}

map<int, string> FindWordsPositionsInTemplate(BohrTree& bohrTree, const string& tpl, const vector<string>& pattern)
{
	map<int, string> wordsPositions;
	int suffLinkVertex = 0;
	for (int i = 0; i < tpl.length(); i++)
	{
		suffLinkVertex = GetAutoMove(bohrTree, suffLinkVertex, tpl[i]);
		AddPosotionIfWord(bohrTree, suffLinkVertex, i + 1, pattern, wordsPositions);
	}

	return wordsPositions;
}

string ExpandTemplate(string const& tpl, map<string, string> const& params)
{
	vector<string> wordsForReplace = GetWordsForReplace(params);
	BohrTree bohrTree = GetBohrTree(wordsForReplace);
	map<int, string> wordsPositions = FindWordsPositionsInTemplate(bohrTree, tpl, wordsForReplace);
	string expandedTemplate = tpl;
	map<string, string> pattern = params;

	for (pair<int, string> wordPosition : wordsPositions)
	{
		expandedTemplate.replace(wordPosition.first, wordPosition.second.length(), pattern[wordPosition.second]);
	}

	return expandedTemplate;
}