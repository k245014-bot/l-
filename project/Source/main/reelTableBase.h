#pragma once
#include <string>
#include <vector>
#include <map>

namespace
{

	static const int SYMBOL_MAX = 3;
}

class CsvReader;

class ReelTableBase
{
public:
	ReelTableBase(std::string filename);
	~ReelTableBase();

	std::map<int, std::vector<std::vector<int>>> GetFirstLines() { return stopLines; }
	std::map<int, std::vector<std::vector<int>>> GetSecondLines() { return secondStopLines; }

	int GetStopLine(int frames, int hitSymbol, int count);
	
	int GetStopLine(int frames, std::string index);

	void AddSecondLines(std::string filename);
	void AddThirdLines(std::string filename);
	void AddSecondLines(std::string filename, std::string index);

protected:

	CsvReader* csv;

	std::vector<std::vector<int>> testStopLines1;
	std::vector<std::vector<int>> testStopLines2;
	std::vector<std::vector<int>> testStopLines3;

	std::map<int, std::vector<std::vector<int>>> stopLines;
	std::map<int, std::vector<std::vector<int>>> secondStopLines;
	std::map<int, std::vector<std::vector<int>>> thirdStopLines;

	std::map<std::string, std::vector<std::vector<int>>> otherStopLines;

	int order;
};

