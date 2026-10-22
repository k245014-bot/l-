#pragma once
#include "../Common/Object/objectBase.h"

namespace
{
	//static const int MAX_RAND = 0xFFFF;
	static const int BET_MAX = 3;
	static const int WAIT_MAX = 4.1f;
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
		START,
		WAIT,
		SPEEN,
		RESULT,
		RESET,
	};

	enum Input_ID
	{
		NONE=0,
		BET,
		LEVER,
		LEFT,
		MIDDLE,
		RIGHT,

		NUM
	};

	FlagLottery* GetFlagData() { return flag; }
	Reel* GetReelData() { return reel; }
	Main_State GetState() { return state; }
	bool GetAllPush();
	bool GetDontPush();

	bool CheckState(int id);
	void ResultCheck();
	void ResetCheck();

	//è¨ñÇ™ëµÇ§
	void SymbolAligned();

private:

	struct Input_Data
	{
		int setKey;
		bool active;
		bool rock;
	};

	FlagLottery* flag;
	CreditMedal* medal;
	Reel* reel;

	int count;
	Main_State state;

	bool betSkip;

	Input_Data input[NUM];
	float waitTime;

	void StartUpdate();
	void SpeenUpdate();
	void WaitUpdate();
	void ResultUpdate();
	void ResetUpdate();

	void SetInput(int index,int key);
};
