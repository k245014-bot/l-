#include "reel.h"
#include "time.h"
#include "mainControl.h"
#include "reelTableBase.h"
#include "flagLottery.h"
#include "../Screen.h"
#include "../csvReader.h"
#include "../imageSynthesis.h"
#include "../randomInput.h"
#include "../input/inputManager.h"

Reel::Reel(MainControl* data)
{
	mainData = data;

	LoadhImage("data/texture/reel.png");
	position.x = Screen::WIDTH / 4 - 20.0f;
	position.y = Screen::HEIGHT / 2 - 81.0f;

	char filename[40];
	sprintf_s<40>(filename, "data/csv/reel/%03d.csv", 1);
	csv = new CsvReader(filename);

	for (int y = 0; y < csv->GetLines(); y++)
	{
		std::vector<int> line;
		for (int x = 0; x < csv->GetColumns(y); x++)
		{
			int c = csv->GetInt(y, x);
			line.push_back(c);
		}
		reel.push_back(line);
	}

	//小役用に値を代入
	symbol = reel;



	for (int i = 0; i < MAX_LINE; i++)
	{
		sprintf_s<40>(filename, "data/csv/hitLine/%02d.csv", i + 1);
		csv->AddFaile(filename);

		for (int y = 0; y < csv->GetLines(); y++)
		{
			std::vector<int> line;
			for (int x = 0; x < csv->GetColumns(y); x++)
			{
				int c = csv->GetInt(y, x);
				line.push_back(c);
			}

			hitSymbolLines[i].push_back(line);
		}

	}

	is = new ImageSynthesis;
	rand = new Random;


	//ベースの画像
	int line = LoadGraph("data/texture/20.png");

	GetGraphSize(line, &imageW, &imageH);

	//合わせる画像
	symbolHandle.emplace(1, LoadGraph("data/texture/Bell_3.png"));
	symbolHandle.emplace(2, LoadGraph("data/texture/replay.png"));
	symbolHandle.emplace(3, LoadGraph("data/texture/suica_ver1.1.png"));
	symbolHandle.emplace(4, LoadGraph("data/texture/cherry.png"));
	symbolHandle.emplace(5, LoadGraph("data/texture/blank.png"));
	symbolHandle.emplace(6, LoadGraph("data/texture/bar_3.png"));
	symbolHandle.emplace(7, LoadGraph("data/texture/7ten_2.png"));
	symbolHandle.emplace(8, LoadGraph("data/texture/7ten_1.png"));
	symbolHandle.emplace(9, LoadGraph("data/texture/maseki.png"));

	//合わせた画像のハンドラ
	reelData[Reel_ID::LEFT].symbolListImage = is->Create(line, symbol, symbolHandle, 1, SYMBOL_SIZE);
	reelData[Reel_ID::MIDDLE].symbolListImage = is->Create(line, symbol, symbolHandle, 2, SYMBOL_SIZE);
	reelData[Reel_ID::RIGHT].symbolListImage = is->Create(line, symbol, symbolHandle, 3, SYMBOL_SIZE);

	for (int i = 0; i < Reel_ID::ID_NUM; i++)
	{
		reelData[i].cell = 0;
		reelData[i].stop = false;
		reelData[i].slip = false;
		reelData[i].slipStop = false;
		reelData[i].stopSpeed = 0;
		//reelData[i].scroll = -180.0f;
		reelData[i].scroll = -SYMBOL_SIZE * 3;

		reelData[i].slipCount = 0;
		//reelData[i].snapTarget = -180.0f;
		reelData[i].snapTarget = -SYMBOL_SIZE * 3;

		reelData[i].prevFrame = 3;

		reelData[i].currentFrame = 0;
	}


	first = false;

	hitSymbol = 0;
	resetTime = 0;
	pushWaitTime = 0;
	stopIndex = -1;
	reachSymbol = -1;

	GetGraphSize(hImage, nullptr, &reelH);

	reelTable[Reel_ID::LEFT] = new ReelTableBase("data/csv/table/csv/left/%02d.csv");
	reelTable[Reel_ID::MIDDLE] = new ReelTableBase("data/csv/table/csv/middle/%02d.csv");
	reelTable[Reel_ID::RIGHT] = new ReelTableBase("data/csv/table/csv/right/%02d.csv");


	reelCover = LoadGraph("data/texture/reelBuller.png");
}

Reel::~Reel()
{
}

void Reel::Update()
{
}

void Reel::Draw()
{
}

void Reel::SetPush(int index, bool active)
{
}

void Reel::SetSymbol(int symbol)
{
}

float Reel::GetStopLine(std::map<int, std::vector<std::vector<int>>> data, int frames)
{
	for (const auto& itr : data)
	{
		//当選した小役のcsvが来るまで回す
		if (itr.first != hitSymbol)
		{
			continue;
		}

		return itr.second[frames][0];
	}
}

void Reel::Reset()
{

}

void Reel::Speen(int index)
{
}

void Reel::Stop(int index)
{
}

void Reel::Gap(int index)
{
}

void Reel::Scroll()
{
}

float Reel::CalcNearScroll(float in_scroll)
{
	return 0.0f;
}

void Reel::ShitSelect(int index)
{
}

void Reel::SearchSymbol(int index, int in_symbol)
{
}

void Reel::ScrollCheck(int index)
{
}

void Reel::FlameMove(int index)
{
}

void Reel::SymbolAligned()
{
}

void Reel::ReelReset(int index)
{
}

bool Reel::AllSlipStop()
{
	return false;
}

bool Reel::AllReelStop()
{
	return false;
}

int Reel::GetSymbolFrame(int frame)
{
	return 0;
}
