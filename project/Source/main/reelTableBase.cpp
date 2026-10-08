#include "reelTableBase.h"
#include "../csvReader.h"

ReelTableBase::ReelTableBase(std::string filename)
{
	char filenames[40];
	csv = new CsvReader;

	//左リールの停止テーブル
	for (int i = 0; i < SYMBOL_MAX; i++)
	{
		sprintf_s<40>(filenames, filename.c_str(), i + 1);
		csv->AddFaile(filenames);
		int rows = csv->GetLines();
		int cols = csv->GetColumns(0);
		stopLines[i].resize(cols);

		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				int c = csv->GetInt(y, x);
				stopLines[i][x].push_back(c);
			}
		}

	}


}



ReelTableBase::~ReelTableBase()
{
	delete csv;
}


int ReelTableBase::GetStopLine(int frames, int hitSymbol, int count)
{

	for (const auto& itr : stopLines)
	{
		//当選した小役のcsvが来るまで回す
		if (itr.first != count)
		{
			continue;
		}

		return itr.second[hitSymbol * 2][frames];
	}

	//switch (count)
	//{
	//case 1:

	//	//return testStopLines1[hitSymbol * 2][frames];

	//	for (const auto& itr : leftStopLines)
	//	{
	//		//当選した小役のcsvが来るまで回す
	//		if (itr.first != count)
	//		{
	//			continue;
	//		}

	//		return itr.second[hitSymbol * 2][frames];
	//	}

	//	break;

	//case 2:

	//	//return testStopLines2[hitSymbol * 2][frames];

	//	for (const auto& itr : middleStopLines)
	//	{
	//		//当選した小役のcsvが来るまで回す
	//		if (itr.first != hitSymbol)
	//		{
	//			continue;
	//		}

	//		return itr.second[hitSymbol * 2][frames];
	//	}
	//	break;

	//case 3:

	//	for (const auto& itr : rightStopLines)
	//	{
	//		//当選した小役のcsvが来るまで回す
	//		if (itr.first != hitSymbol)
	//		{
	//			continue;
	//		}


	//		return itr.second[hitSymbol * 2][frames];
	//	}
	//	break;

	//}
}



int ReelTableBase::GetStopLine(int frames, std::string index)
{
	for (const auto& itr : otherStopLines)
	{
		//当選した小役のcsvが来るまで回す
		if (itr.first == index)
		{
			return itr.second[frames][0];
		}
	
	}
}

void ReelTableBase::AddSecondLines(std::string filename)
{

	char filenames[40];

	//左リールの停止テーブル
	for (int i = 0; i < SYMBOL_MAX; i++)
	{
		sprintf_s<40>(filenames, filename.c_str(), i);
		csv->AddFaile(filenames);

		for (int y = 0; y < csv->GetLines(); y++)
		{
			std::vector<int> line;
			for (int x = 0; x < csv->GetColumns(y); x++)
			{
				int c = csv->GetInt(y, x);
				line.push_back(c);
			}

			secondStopLines[i].push_back(line);
		}
	}
}

void ReelTableBase::AddThirdLines(std::string filename)
{
	char filenames[40];

	//左リールの停止テーブル
	for (int i = 0; i < SYMBOL_MAX; i++)
	{
		sprintf_s<40>(filenames, filename.c_str(), i);
		csv->AddFaile(filenames);

		for (int y = 0; y < csv->GetLines(); y++)
		{
			std::vector<int> line;
			for (int x = 0; x < csv->GetColumns(y); x++)
			{
				int c = csv->GetInt(y, x);
				line.push_back(c);
			}

			thirdStopLines[i].push_back(line);
		}
	}
}

void ReelTableBase::AddSecondLines(std::string filename, std::string index)
{
	csv->AddFaile(filename.c_str());

	for (int y = 0; y < csv->GetLines(); y++)
	{
		std::vector<int> line;
		for (int x = 0; x < csv->GetColumns(y); x++)
		{
			int c = csv->GetInt(y, x);
			line.push_back(c);
		}

		otherStopLines[index].push_back(line);
	}
}
