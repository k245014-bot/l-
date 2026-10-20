#pragma once
#include "../Common/Object/objectBase.h"

namespace
{
	//static const int MAX_RAND = 0xFFFF;
}

class FlagLottery;
class CreditMedal;
class Reel;

class MainControl :public ObjectBase
{
public:
	MainControl();
	~MainControl();
	void Update()override;
	void Draw()override;

	enum  Main_State
	{
		STAY,
		BET,
		SPEEN,
		WAIT,
		RESULT,
		RESET,
	};

	FlagLottery* GetFlagData() { return flag; }
	Reel* GetReelData() { return reel; }
	bool GetAllPush();
	bool GetDontPush();

	bool CheckState(int id);
	void ResultCheck();
	void ResetCheck();

	//è¨ñÇ™ëµÇ§
	void SymbolAligned();

private:

	FlagLottery* flag;
	CreditMedal* medal;
	Reel* reel;

	int count;
	Main_State state;

	bool betSkip;

	void BetUpdate();
	void SpeenUpdate();
	void WaitUpdate();
	void ResultUpdate();
	void ResetUpdate();
};
