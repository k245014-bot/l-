#pragma once
#include "../Common/Object/objectBase.h"

class CreditMedal :public ObjectBase
{
public:
	CreditMedal();
	~CreditMedal();
	void Update()override;
	void Draw()override;

	void BetMedal(int medal);
	void PayMedal(int medal);

private:

	int myMedal;

};
