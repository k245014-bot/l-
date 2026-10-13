#pragma once
#include "../objectBase.h"

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

private:

	FlagLottery* flag;
	CreditMedal* medal;
	Reel* reel;
};
