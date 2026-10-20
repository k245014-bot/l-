#pragma once
#include "../Common/Object/objectBase.h"
#include "../Common/randomInput.h"
#include <map>
#include <iostream>

class FlagLottery :public ObjectBase
{
public:
	FlagLottery();
	~FlagLottery();
	void Update()override;
	void Draw()override {};

	void SetRand();
	void SymbolReset();
	void Reset();

	enum ID
	{
		HAZURE = 0,             // ハズレ

		BELL = 1,               // ベル
		REPLAY = 2,             // リプレイ
		WATERMELON = 3,         // スイカ

		CHERRY_A_WEAK = 4,      // 弱チェリーA
		CHERRY_B_WEAK = 5,      // 弱チェリーB

		CHERRY_A_STRONG = 6,    // 強チェリーA
		CHERRY_B_STRONG = 7,    // 強チェリーB

		CHANCE = 8,             // チャンス目A
		CHANCE_REPLAY = 9,      // チャンス目リプレイ

		BELL_ORDER_A = 14,      // 押し順ベル(中,右,左)
		BELL_ORDER_B = 15,      // 押し順ベル(中,左,右)
		BELL_ORDER_C = 16,      // 押し順ベル(右,中,左)
		BELL_ORDER_D = 17,      // 押し順ベル(右,左,中)


		SYMBOL_MAX
	};

	const int GetPayMedal(const int& index);
	const int GetSymbol();

private:


	int hit, prevHit;


	//各小役の払い出し枚数
	int payMedal[ID::SYMBOL_MAX];
};
