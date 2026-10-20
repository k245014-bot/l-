#include "csvReader.h"
#include <fstream>
#include <assert.h>

CsvReader::CsvReader(std::string filename)
{
	all.clear();

	std::ifstream ifs(filename);
	if (!ifs) return;

	// BOM Skipする
	unsigned char BOMS[] = { 0xEF, 0xBB, 0xBF };
	bool found = true;
	for (int i=0; i<3; i++) {
		if (ifs.get() != BOMS[i]) {
			found = false;
			break;
		}
	}
	if (!found)
		ifs.seekg(std::ios_base::beg);

	// データを読む
	std::string lineStr;
	while (getline(ifs, lineStr)) {
		while (true) {
			int dq = 0;
			for (int i=0; i<lineStr.size(); i++) {
				if (lineStr[i] == '"')
					dq++;
			}
			if (dq % 2 == 0)
				break;
			std::string s;
			getline(ifs, s);
			lineStr += "\n" + s;
		}
		for (auto it = lineStr.begin(); it!=lineStr.end();) {
			if (*it=='"')
				it = lineStr.erase(it);
			if (it != lineStr.end())
				it++;
		}

		// 行内を,で切り分ける
		LINEREC lineRecord;
		int top = 0;
		bool indq = false;
		for (int n = 0; n < lineStr.size(); n++) {
			if (lineStr[n]==',') {
				if (!indq) {
					lineRecord.record.emplace_back(lineStr.substr(top, (size_t)(n - top)));
					top = n + 1;
				}
			} else if (lineStr[n] == '"')
				indq = !indq;
		}
		lineRecord.record.emplace_back(lineStr.substr(top, lineStr.size() - top));
		all.emplace_back(lineRecord);
	}
	ifs.close();
}

CsvReader::CsvReader()
{
	all.clear();
}

CsvReader::~CsvReader()
{
	for (auto rec : all)
		rec.record.clear();
	all.clear();
}

int CsvReader::GetLines()
{
	return all.size();
}

int CsvReader::GetColumns(int line)
{
	assert(line < GetLines());
	return all[line].record.size();
}

std::string CsvReader::GetString(int line, int column)
{
	assert(line < GetLines());
	if (column >= GetColumns(line))
		return "";
	return all[line].record[column];
}

int CsvReader::GetInt(int line, int column)
{
	std::string str = GetString(line, column);
	if (str=="") {
		return 0;
	}
	return std::stoi(str);
}

float CsvReader::GetFloat(int line, int column)
{
	std::string str = GetString(line, column);
	if (str == "") {
		return 0.0f;
	}
	return std::stof(str);
}

void CsvReader::AddFaile(std::string filename)
{
	all.clear();

	std::ifstream file(filename);
	std::string str;


	//一行づつ読む
	while (std::getline(file, str))
	{
		//OutputDebugString(str.c_str());
		//OutputDebugString("\n");

		LINEREC line;

		// strを,ごとにばらす(行ごとに文字列の分割)
		int idx;
		//,が見つから無くなるまで代入
		//nposは何もない時に返る
		while ((idx = str.find(',')) != std::string::npos)
		{
			//substr文字列を抜き出す
			//今の文字列を代入する
			std::string s1 = str.substr(0, idx);
			//,の右の文字列にずらす
			str = str.substr(idx + 1);
			//一文字を要素を入れる
			line.record.push_back(s1);
		}

		//ループが抜けたら
		//最後の文字を入れる
		line.record.push_back(str);
		////一行終わり
		all.push_back(line);
	}
	file.close();
}
