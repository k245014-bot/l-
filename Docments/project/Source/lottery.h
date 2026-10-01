#pragma once
#include "objectBase.h"
#include <map>
#include <iostream>

namespace
{
	static const int MAX_RAND = 0x10000;
}

class Symbol;

class Lottery:public ObjectBase
{
public:
	Lottery();
	~Lottery();
	void Update()override;
	void Draw()override;

	//enum Symbol
	//{
	//	BELL,				//ベル
	//	REPLAY,				//リプレイ
	//	WATERMELON_A,		//スイカA
	//	WATERMELON_B,		//スイカB
	//	CHERRY,				//弱チェリー
	//	SYMBOL_MAX
	//};

private:

	Symbol* symbol;

	//int payMedal[Symbol::SYMBOL_MAX];
	//std::multimap<int, float> symbol;

	int count;

	bool push;

	int r;

	bool hit;

	bool reset;
};

inline 	int MainRand()
{
	return rand() % MAX_RAND;
}