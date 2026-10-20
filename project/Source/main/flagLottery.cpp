#include "flagLottery.h"

extern "C" int FlagSymbol();

FlagLottery::FlagLottery() : hit(ID::HAZURE),prevHit(ID::HAZURE),payMedal{}
{
	
	// ========================================
   // 各小役の払い出し枚数
   // ========================================

   // ベル
	payMedal[ID::BELL] = 2;

	// リプレイ
	payMedal[ID::REPLAY] = 0;

	// スイカ
	payMedal[ID::WATERMELON] = 3;

	// 弱チェリー
	payMedal[ID::CHERRY_A_WEAK] = 0;
	payMedal[ID::CHERRY_B_WEAK] = 0;

	// 強チェリー
	payMedal[ID::CHERRY_A_STRONG] = 0;
	payMedal[ID::CHERRY_B_STRONG] = 0;

	// チャンス目
	payMedal[ID::CHANCE] = 0;
	payMedal[ID::CHANCE_REPLAY] = 0;

	// 押し順ベル
	// 払い出し枚数は仮に0枚
	payMedal[ID::BELL_ORDER_A] = 0;
	payMedal[ID::BELL_ORDER_B] = 0;
	payMedal[ID::BELL_ORDER_C] = 0;
	payMedal[ID::BELL_ORDER_D] = 0;
}

FlagLottery::~FlagLottery()
{
}

void FlagLottery::Update()
{
}

void FlagLottery::SetRand()
{
	hit = FlagSymbol();
}

void FlagLottery::SymbolReset()
{
	prevHit = hit;
	hit = ID::HAZURE;
}

void FlagLottery::Reset()
{
	hit = ID::HAZURE;
}


const int FlagLottery::GetPayMedal(const int& index)
{
	if (index < 0 || index >= ID::SYMBOL_MAX)
	{
		return 0;
	}
	return payMedal[index];
}

const int FlagLottery::GetSymbol()
{
	return hit;
}
