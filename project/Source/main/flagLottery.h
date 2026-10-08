#pragma once
#include "../objectBase.h"
#include "../randomInput.h"
#include <map>
#include <iostream>

namespace
{
	static const int MAX_RAND = 65536;

	//小役確率
	static const float BELLA_RAND = MAX_RAND / 8.2f;			//右下がりベル

	static const float REPLAY_RAND = MAX_RAND / 8.7f;				//リプレイ
	static const float CHANCE_REPLAY_RAND = MAX_RAND / 198.6f;		//チャンスリプレイ(勝舞揃い)

	static const float CHANCE_RAND = MAX_RAND / 199.2f;				//チャンス目
	static const float CHERRY_WEAK_RAND	= MAX_RAND / 199.2f;		//弱チェリーA
	static const float CHERRY_STRONG_RAND	= MAX_RAND / 397.2f;	//強チェリーA
	
	static const float WATERMELON_RAND = MAX_RAND / 79.9f;			//スイカ
	
	static const float BELL_ORDER_RAND = MAX_RAND / 5.58f;			//押し順ベル

	
}

class Random;

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
		BELL = 1,			//ベル
		REPLAY = 2,			//リプレイ
		WATERMELON = 3,		//スイカ
		CHERRY_A_WEAK = 4,	//弱チェリーA
		CHERRY_B_WEAK = 5,	//弱チェリーB
		CHERRY_A_STRONG = 6,//強チェリーA
		CHERRY_B_STRONG = 7,//強チェリーB
		CHANCE = 8,			//チャンス目A
		CHANCE_REPLAY = 9,		//チャンスリプレイ(勝舞揃い)

		BELL_ORDER_A = 14, //押し順ベル(中,右,左)
		BELL_ORDER_B = 15, //押し順ベル(中,左,右)
		BELL_ORDER_C = 16, //押し順ベル(右,中,左)
		BELL_ORDER_D = 17, //押し順ベル(右,左,中)


		SYMBOL_MAX
	};

	const int GetPayMedal(const int& index);
	const int GetSymbol();

private:

	enum  Rand_ID
	{

		R_CHERRY_A_STRONG = 1,	//強チェリーA
		R_CHERRY_B_STRONG = 2,	//強チェリーB
		R_CHERRY_A_WEAK = 3,	//弱チェリーA
		R_CHERRY_B_WEAK = 4,	//弱チェリーB
		R_CHANCE = 5,			//チャンス目
		R_CHANCE_REPLAY = 6,	//チャンスリプレイ(勝舞揃い)
		R_WATERMELON = 7,  //スイカ
		R_REPLAY = 8,	//リプレイ
		R_BELL = 9,	//ベル

		R_BELL_ORDER_A = 14, //押し順ベル(中,右,左)
		R_BELL_ORDER_B = 15, //押し順ベル(中,左,右)
		R_BELL_ORDER_C = 16, //押し順ベル(右,中,左)
		R_BELL_ORDER_D = 17, //押し順ベル(右,左,中)


		R_SYMBOL_MAX
	};


	int hit, prevHit;

	float mainRand;

	std::map<Rand_ID, int> priority;

	std::map<Rand_ID, ID> hitSymbol;

	int ratio;

	//各小役の払い出し枚数
	int payMedal[ID::SYMBOL_MAX];

	Random* rand;

};
