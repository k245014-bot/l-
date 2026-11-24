#include "flagLottery.h"

FlagLottery::FlagLottery()
{
	//
	////強チェリーAの乱数
	//priority.emplace(Rand_ID::R_CHERRY_A_STRONG, round(CHERRY_STRONG_RAND));
	//
	////強チェリーBの乱数
	//priority.emplace(Rand_ID::R_CHERRY_B_STRONG, round(CHERRY_STRONG_RAND));

	////弱チェリーAの乱数
	//priority.emplace(Rand_ID::R_CHERRY_A_WEAK, round(CHERRY_WEAK_RAND));
	//
	////弱チェリーBの乱数
	//priority.emplace(Rand_ID::R_CHERRY_B_WEAK, round(CHERRY_WEAK_RAND));

	////チャンス目の乱数
	//priority.emplace(Rand_ID::R_CHANCE, round(CHANCE_RAND));
	////チャンス目の乱数
	//priority.emplace(Rand_ID::R_CHANCE_REPLAY, round(CHANCE_RAND));

	////スイカの乱数
	//priority.emplace(Rand_ID::R_WATERMELON, round(WATERMELON_RAND));

	////リプレイの乱数
	//priority.emplace(Rand_ID::R_REPLAY, round(REPLAY_RAND));

	////ベルの乱数
	//priority.emplace(Rand_ID::R_BELL, round(BELLA_RAND));

	////押し順ベルAの乱数
	//priority.emplace(Rand_ID::R_BELL_ORDER_A, round(BELL_ORDER_RAND));
	//
	////押し順ベルBの乱数
	//priority.emplace(Rand_ID::R_BELL_ORDER_B, round(BELL_ORDER_RAND));

	////押し順ベルCの乱数
	//priority.emplace(Rand_ID::R_BELL_ORDER_C, round(BELL_ORDER_RAND));

	////押し順ベルDの乱数
	//priority.emplace(Rand_ID::R_BELL_ORDER_D, round(BELL_ORDER_RAND));


	hit = HAZURE;

	/*ratio = 0;
	mainRand = 0;*/
	prevHit = HAZURE;
	//rand = new Random();


	payMedal[BELLA] = 2;
	payMedal[BELLB] = 2;
	payMedal[BELLC] = 2;
	payMedal[BELLD] = 2;
	payMedal[REPLAYA] = 0;
	payMedal[REPLAYB] = 0;
	payMedal[REPLAYC] = 0;
	payMedal[REPLAYD] = 0;
	payMedal[WATERMELON] = 3;
	payMedal[CHERRY_A_WEAK] = 0;
	payMedal[CHERRY_B_WEAK] = 0;
	payMedal[CHERRY_A_STRONG] = 0;
	payMedal[CHERRY_B_STRONG] = 0;
	payMedal[CHANCE] = 0;
	payMedal[CHANCE_REPLAY] = 0;
	payMedal[BELL_ORDER_A] = 0;
	payMedal[BELL_ORDER_B] = 0;
	payMedal[BELL_ORDER_C] = 0;
	payMedal[BELL_ORDER_D] = 0;

	/*hitSymbol.emplace(Rand_ID::R_BELL, ID::BELL);
	hitSymbol.emplace(Rand_ID::R_REPLAY, ID::REPLAY);
	hitSymbol.emplace(Rand_ID::R_WATERMELON, ID::WATERMELON);
	hitSymbol.emplace(Rand_ID::R_CHERRY_A_WEAK, ID::CHERRY_A_WEAK);
	hitSymbol.emplace(Rand_ID::R_CHERRY_B_WEAK, ID::CHERRY_B_WEAK);
	hitSymbol.emplace(Rand_ID::R_CHERRY_A_STRONG, ID::CHERRY_A_STRONG);
	hitSymbol.emplace(Rand_ID::R_CHERRY_B_STRONG, ID::CHERRY_B_STRONG);
	hitSymbol.emplace(Rand_ID::R_CHANCE, ID::CHANCE);
	hitSymbol.emplace(Rand_ID::R_CHANCE_REPLAY, ID::CHANCE_REPLAY);
	hitSymbol.emplace(Rand_ID::R_BELL_ORDER_A, ID::BELL_ORDER_A);
	hitSymbol.emplace(Rand_ID::R_BELL_ORDER_B, ID::BELL_ORDER_B);
	hitSymbol.emplace(Rand_ID::R_BELL_ORDER_C, ID::BELL_ORDER_C);
	hitSymbol.emplace(Rand_ID::R_BELL_ORDER_D, ID::BELL_ORDER_D);*/
}

FlagLottery::~FlagLottery()
{
	//delete rand;
}

void FlagLottery::Update()
{
}

void FlagLottery::SetRand()
{
	////乱数の抽選
	//mainRand = rand->Input(0, MAX_RAND);

	////プライオリティを参照して小役の抽選諸々
	//for (auto itr : priority)
	//{
	//	Rand_ID i = itr.first;
	//	int sum = (itr.second) + ratio;
	//	if (mainRand >= ratio && mainRand < sum)
	//	{
	//		hit = hitSymbol.at(itr.first);
	//		break;
	//	}
	//	ratio += itr.second;
	//}

	//hit = ID::CHERRY_A_STRONG;

	//hit = ID::BELL;

	hit = FlagSymbol();

	if (hit < 0 || hit >= SYMBOL_MAX)
	{
		hit = HAZURE;
	}
}

void FlagLottery::SymbolReset()
{
	prevHit = hit;
	hit = HAZURE;
	//ratio = 0;
}

void FlagLottery::Reset()
{
	hit = 0;
	//ratio = 0;
}


const int FlagLottery::GetPayMedal(const int& index)
{
	if (index < 0 || index >= SYMBOL_MAX)
	{
		return 0;
	}
	return payMedal[index];
}

const int FlagLottery::GetSymbol()
{
	return hit;
}
