#include "lottery.h"
#include "symbol.h"

Lottery::Lottery()
{

	count = 0;

	r = 0;
	push = false;
	hit = false;
	reset = false;

	symbol = new Symbol();

	srand((unsigned)time(NULL));
}

Lottery::~Lottery()
{
}

void Lottery::Update()
{
	if (push == false && count > 60)
	{
		if (CheckHitKey(KEY_INPUT_Z))
		{
			hit = false;
			push = true;
			count = 0;
		}
	}
	else if (push == true)
	{
		symbol->Reset();
		symbol->Create();
		symbol->Check();


		push = false;
	}
	count++;
	

}

void Lottery::Draw()
{

	if (push == false&& count > 60)
	{
		DrawFormatString(100, 0, GetColor(255, 255, 255), "Z押せ");
	}

	//イテレータの中身がある場合
	if (symbol->GetMap().empty() == false)
	{
		for (const auto& itr : symbol->GetMap())
		{
			//キー
			switch (itr.first)
			{
			case Symbol::BELL:

				if (symbol->GetHit(symbol->BELL) == true)
				{
					DrawFormatString(100, 100, GetColor(255, 255, 0), "ベル");
				}

				break;
			case Symbol::REPLAY:

				if (symbol->GetHit(symbol->REPLAY) == true)
				{
					DrawFormatString(100, 100, GetColor(0, 255, 255), "リプレイ");
				}

				break;
			case Symbol::WATERMELON_A:
				break;
			case Symbol::WATERMELON_B:
				break;
			case Symbol::CHERRY:
				break;
			default:
				DrawFormatString(100, 100, GetColor(255, 255, 255), "ハズレ");

				break;
			}
		}
	}
}


