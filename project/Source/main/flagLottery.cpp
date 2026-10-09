#include "flagLottery.h"

FlagLottery::FlagLottery()
{
	
	//強チェリーAの乱数
	priority.emplace(Rand_ID::R_CHERRY_A_STRONG, round(CHERRY_STRONG_RAND));
	
	//強チェリーBの乱数
	priority.emplace(Rand_ID::R_CHERRY_B_STRONG, round(CHERRY_STRONG_RAND));

	//弱チェリーAの乱数
	priority.emplace(Rand_ID::R_CHERRY_A_WEAK, round(CHERRY_WEAK_RAND));
	
	//弱チェリーBの乱数
	priority.emplace(Rand_ID::R_CHERRY_B_WEAK, round(CHERRY_WEAK_RAND));

	//チャンス目の乱数
	priority.emplace(Rand_ID::R_CHANCE, round(CHANCE_RAND));
	//チャンス目の乱数
	priority.emplace(Rand_ID::R_CHANCE_REPLAY, round(CHANCE_RAND));

	//スイカの乱数
	priority.emplace(Rand_ID::R_WATERMELON, round(WATERMELON_RAND));

	//リプレイの乱数
	priority.emplace(Rand_ID::R_REPLAY, round(REPLAY_RAND));

	//ベルの乱数
	priority.emplace(Rand_ID::R_BELL, round(BELLA_RAND));
	

	hit = 0;

	ratio = 0;
	mainRand = 0;
	prevHit = 0;
	rand = new Random();



	payMedal[ID::BELL] = 2;
	payMedal[ID::REPLAY] = 0;
	payMedal[ID::WATERMELON] = 3;
	payMedal[ID::CHERRY_A_WEAK] = 0;
	payMedal[ID::CHERRY_B_WEAK] = 0;
	payMedal[ID::CHERRY_A_STRONG] = 0;
	payMedal[ID::CHERRY_B_STRONG] = 0;
	payMedal[ID::CHANCE] = 0;
	payMedal[ID::CHANCE_REPLAY] = 0;

	hitSymbol.emplace(Rand_ID::R_BELL, ID::BELL);
	hitSymbol.emplace(Rand_ID::R_REPLAY, ID::REPLAY);
	hitSymbol.emplace(Rand_ID::R_WATERMELON, ID::WATERMELON);
	hitSymbol.emplace(Rand_ID::R_CHERRY_A_WEAK, ID::CHERRY_A_WEAK);
	hitSymbol.emplace(Rand_ID::R_CHERRY_B_WEAK, ID::CHERRY_B_WEAK);
	hitSymbol.emplace(Rand_ID::R_CHERRY_A_STRONG, ID::CHERRY_A_STRONG);
	hitSymbol.emplace(Rand_ID::R_CHERRY_B_STRONG, ID::CHERRY_B_STRONG);
	hitSymbol.emplace(Rand_ID::R_CHANCE, ID::CHANCE);
	hitSymbol.emplace(Rand_ID::R_CHANCE_REPLAY, ID::CHANCE_REPLAY);
}

FlagLottery::~FlagLottery()
{
	delete rand;
}

void FlagLottery::Update()
{
}

void FlagLottery::SetRand()
{
	//乱数の抽選
	mainRand = rand->Input(0, MAX_RAND);

	//プライオリティを参照して小役の抽選諸々
	for (auto itr : priority)
	{
		Rand_ID i = itr.first;
		int sum = (itr.second) + ratio;
		if (mainRand >= ratio && mainRand < sum)
		{
			hit = hitSymbol.at(itr.first);
			break;
		}
		ratio += itr.second;
	}

}

void FlagLottery::SymbolReset()
{
	prevHit = hit;
	hit = 0;
	ratio = 0;
}

void FlagLottery::Reset()
{
	hit = 0;
	ratio = 0;
}


const int FlagLottery::GetPayMedal(const int& index)
{
	return payMedal[index];
}

const int FlagLottery::GetSymbol()
{
	return hit;
}
