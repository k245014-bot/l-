#include "creditMedal.h"

CreditMedal::CreditMedal()
{
	myMedal = 0;
}

CreditMedal::~CreditMedal()
{
}

void CreditMedal::Update()
{
}

void CreditMedal::Draw()
{
}

void CreditMedal::BetMedal(int medal)
{
	myMedal -= medal;
}

void CreditMedal::PayMedal(int medal)
{
	myMedal += medal;
}
