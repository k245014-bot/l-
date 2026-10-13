#include "reel.h"
#include "time.h"
#include "mainControl.h"
#include "reelTableBase.h"
#include "../Screen.h"
#include "../csvReader.h"
#include "../imageSynthesis.h"
#include "../randomInput.h"
#include "../input/inputManager.h"

Reel::Reel(MainControl* data)
{
	mainData = data;

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
	symbolHandle.emplace(7, LoadGraph("data/texture/red_7.png"));
	symbolHandle.emplace(8, LoadGraph("data/texture/maseki.png"));

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

	/*reelTable[Reel_ID::LEFT] = new ReelTableBase("data/csv/table/csv/left/%02d.csv");
	reelTable[Reel_ID::MIDDLE] = new ReelTableBase("data/csv/table/csv/middle/%02d.csv");
	reelTable[Reel_ID::RIGHT] = new ReelTableBase("data/csv/table/csv/right/%02d.csv");*/


	reelCover = LoadGraph("data/texture/reelBuller.png");
}

Reel::~Reel()
{
	delete csv;
	delete is;

	for (int i = 0; i < Reel_ID::ID_NUM; i++)
	{
		delete reelTable[i];
	}
}

void Reel::Update()
{
	//switch (mainData->GetState())
	//{
	//	//リセット
	//case MainControl::Main_State::STAY:

	//	Reset();

	//	break;
	//case MainControl::Main_State::BET:

	//	break;

	//case MainControl::Main_State::SPEEN:

	//	first = true;

	//	for (int i = 0; i < Reel_ID::ID_NUM; i++)
	//	{
	//		Speen(i);
	//	}


	//	if (++pushWaitTime > 30)
	//	{
	//		for (int i = 0; i < Reel_ID::ID_NUM; i++)
	//		{
	//			//PushCheck(i);

	//			//リールを止める
	//			if (reelData[i].push == true)
	//			{
	//				Stop(i);
	//			}
	//		}

	//		pushWaitTime = 30;
	//	}

	//	if (AllReelStop() == true && AllSlipStop() == true)
	//	{
	//		resetTime += Time::DeltaTime();

	//		float rate = resetTime / RESET_WAIT_TIME;

	//		if (rate >= 1.0f)
	//		{
	//			for (int i = 0; i < Reel_ID::ID_NUM; i++)
	//			{
	//				FlameMove(i);
	//				ScrollCheck(i);
	//			}
	//			mainData->ResultCheck();
	//			resetTime = 0;

	//		}
	//	}

	//	break;

	//case MainControl::Main_State::RESULT:

	//	SymbolAligned();

	//	mainData->ResetCheck();

	//	Reset();

	//	break;

	//}

	Scroll();
}

void Reel::Draw()
{
	//リールの描画
	for (int i = 0; i < Reel_ID::ID_NUM; i++)
	{
		//画像を少し大きくしたので
		//補正に18.0fを追加
		reelData[i].cell = ((int)reelData[i].scroll % imageH + reelH);

		float shift = 0;

		if (i < 2)
		{
			shift = -11.0f + (i * 6.0f);
		}
		else
		{
			shift = 2.0f;
		}



		DrawRectGraph((int)position.x + (165 * i) + shift, (int)position.y, 0, reelData[i].cell + imageH, 140, SYMBOL_SIZE * 3, reelData[i].symbolListImage, true);
		DrawRectGraph((int)position.x + (165 * i) + shift, (int)position.y, 0, reelData[i].cell, 140, SYMBOL_SIZE * 3, reelData[i].symbolListImage, true);

	}
}

void Reel::SetPush(int index, bool active)
{
	if (reelData[index].push == true)
	{
		return;
	}

	reelData[index].push = active;
}

void Reel::SetSymbol(int symbol)
{
	hitSymbol = symbol;
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
	for (int i = 0; i < Reel_ID::ID_NUM; i++)
	{
		reelData[i].stop = false;
		reelData[i].slipStop = false;
		reelData[i].push = false;
		pushWaitTime = 0;
		hitSymbol = 0;
		stopIndex = 0;
		reachSymbol = -1;
		reelData[i].stopLine = 0;
		reelData[i].symbolIndex = -1;
	}

	stopIndex = -1;
}

void Reel::Speen(int index)
{
	if (reelData[index].stop == true)
	{
		return;
	}

	int totalSize = (int)SYMBOL_SIZE * reel.size();

	float speed = totalSize / LOOP_TIME;

	reelData[index].scroll -= speed * Time::DeltaTime();
}

void Reel::Stop(int index)
{
	if (reelData[index].slipStop == true)
	{
		return;
	}


	reelData[index].stop = true;

	if (reelData[index].stop == true && reelData[index].slip == false)
	{
		FlameMove(index);

		ScrollCheck(index);

		//小役の検索
		SearchSymbol(index, hitSymbol);

		ShitSelect(index);

		reelData[index].slip = true;

	}

	if (reelData[index].slip == true)
	{


		reelData[index].stopSpeed += Time::DeltaTime();

		//最大0.19いないに止める必要があるので、4分割する
		const float sumTime = reelData[index].slipCount * 0.0475f;

		//0.19秒で終了
		float rate = reelData[index].stopSpeed / sumTime;

		float easedRate = 1.0f - (1.0f - rate) * (1.0f - rate);

		//ターゲットに向かう
		reelData[index].scroll = Lerp(reelData[index].snapStart, reelData[index].snapTarget, easedRate);

		if (rate >= 1.0f || sumTime == 0)
		{
			reelData[index].scroll = reelData[index].snapTarget;

			//速度をリセット
			reelData[index].stopSpeed = 0;

			reelData[index].slip = false;
			reelData[index].slipStop = true;
		}
	}
}

void Reel::Gap(int index)
{
	auto copy = reel;

	for (int y = (int)reel.size() - 1; y > 0; y--)
	{
		reel[y][index] = reel[y - 1][index];
	}

	reel[0][index] = copy[copy.size() - 1][index];
}

void Reel::Scroll()
{
	if (first == false)
	{
		return;
	}

	for (int i = 0; i < Reel_ID::ID_NUM; i++)
	{
		if (reelData[i].slip == false)
		{

			if (reelData[i].scroll <= -SYMBOL_SIZE * MAX_SYMBOL)
			{
				reelData[i].scroll += SYMBOL_SIZE * MAX_SYMBOL;
			}
		}

		FlameMove(i);

		ScrollCheck(i);

	}
}

float Reel::CalcNearScroll(float in_scroll)
{
	float flameIndex = roundf(-in_scroll / (float)SYMBOL_SIZE);

	return -flameIndex * (float)SYMBOL_SIZE;
}

void Reel::ShitSelect(int index)
{
	reelData[index].snapStart = -(reelData[index].prevFrame) * (float)SYMBOL_SIZE;
	reelData[index].snapTarget = -(reelData[index].prevFrame + reelData[index].slipCount) * (float)SYMBOL_SIZE;
}

void Reel::SearchSymbol(int index, int in_symbol)
{
	reelData[index].symbolIndex = GetSymbolFrame(reelData[index].currentFrame);


	int hit = 0;

	if (stopIndex < 0)
	{
		stopIndex = index;
	}


	if (hitSymbol == 7)
		hitSymbol = 5;

	if (hitSymbol == 12)
		hitSymbol = 1;


	hit = reelTable[index]->GetStopLine(reelData[index].symbolIndex, hitSymbol, stopIndex);

	int inSymbol = reelData[index].symbolIndex - hit;

	if (inSymbol < 0)
	{
		inSymbol += (int)reel.size();
	}

	if (inSymbol > 20)
	{
		inSymbol -= (int)reel.size();
	}


	int resultSymbol = hit;


	////滑り数セット
	reelData[index].slipCount = hit;


	reelData[index].symbolIndex -= resultSymbol;

	if (reelData[index].symbolIndex < 0)
	{
		reelData[index].symbolIndex += (int)reel.size();
	}

	if (reelData[index].symbolIndex > 20)
	{
		reelData[index].symbolIndex -= (int)reel.size();
	}
}

void Reel::ScrollCheck(int index)
{
	if (reelData[index].currentFrame != reelData[index].prevFrame)
	{
		// 1コマ移動したよ！
		reelData[index].prevFrame = reelData[index].currentFrame;

		Gap(index);
	}
}

void Reel::FlameMove(int index)
{
	reelData[index].currentFrame = (int)floorf(-reelData[index].scroll / (float)SYMBOL_SIZE);
}

void Reel::SymbolAligned()
{
	/*
	if (hitSymbol == -1)
	{
		return;
	}

	bool hit[Reel_ID::ID_NUM];

	for (int i = 0; i < Reel_ID::ID_NUM; i++)
	{
		hit[i] = false;
	}


	for (const auto& itr : hitSymbolLines)
	{

		if (hitSymbol == mainData->GetSymbol()->CHERRY_WEAK)
		{
			if (itr.first < 5)
			{
				continue;
			}
		}

		for (int y = 0; y < Reel_ID::ID_NUM; y++)
		{
			for (int x = 0; x < reel[y].size(); x++)
			{

				if (hit[x] != 0)
				{
					continue;
				}

				int num = itr.second[y][x];

				if (num == 1 && reel[y][x] == hitSymbol)
				{
					hit[x] = true;
				}

			}

		}

	}

	if (hitSymbol == 4 && hit[Reel_ID::LEFT] == true)
	{
		mainData->SymbolAligned();
	}

	if (hit[Reel_ID::LEFT] == true &&
		hit[Reel_ID::MIDDLE] == true &&
		hit[Reel_ID::RIGHT] == true)
	{
		mainData->SymbolAligned();

	}
	*/
}

void Reel::ReelReset(int index)
{
	int gap = GetSymbolFrame(reelData[index].prevFrame);

	for (int i = 0; i < reel.size(); i++)
	{
		if (gap > 19)
		{
			gap -= reel.size();
		}

		if (gap < 0)
		{
			gap += reel.size();
		}

		reel[i][index] = symbol[gap][index];
		gap++;
	}
}

bool Reel::AllSlipStop()
{
	return (reelData[Reel_ID::LEFT].slipStop == true && reelData[Reel_ID::MIDDLE].slipStop == true && reelData[Reel_ID::RIGHT].slipStop == true);
}

bool Reel::AllReelStop()
{
	return (reelData[Reel_ID::LEFT].push == true && reelData[Reel_ID::MIDDLE].push == true && reelData[Reel_ID::RIGHT].push == true);
}

int Reel::GetSymbolFrame(int frame)
{
	int num = -1;

	if (frame >= 0 && frame <= 5)
	{
		num = (5 - frame);
	}
	else if (frame >= 6 && frame <= MAX_SYMBOL)
	{
		num = (25 - frame);
	}

	if (num < 0)
	{
		num += (int)reel.size();
	}
	if (num > 19)
	{
		num -= (int)reel.size();
	}

	return num;
}
