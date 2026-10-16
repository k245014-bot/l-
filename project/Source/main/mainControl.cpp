#include "mainControl.h"
#include "reel.h"
#include "flagLottery.h"
#include "creditMedal.h"
#include "time.h"

MainControl::MainControl()
{
	SetDrawOrder(110);
	reel = new Reel(this);
	flag = new FlagLottery;
	medal = new CreditMedal;
	count = 0;
	state = Main_State::STAY;
	betSkip = false;
	
	for (int i = 0; i < Input_ID::NUM; i++)
	{
		input[i].active = false;
		input[i].rock = false;
		input[i].setKey = -1;
	}

}

MainControl::~MainControl()
{
	delete reel;
	delete flag;
	delete medal;
}

void MainControl::Update()
{

	SetInput(Input_ID::BET, KEY_INPUT_X);
	SetInput(Input_ID::LEVER, KEY_INPUT_SPACE);
	SetInput(Input_ID::LEFT, KEY_INPUT_LEFT);
	SetInput(Input_ID::MIDDLE, KEY_INPUT_DOWN);
	SetInput(Input_ID::RIGHT, KEY_INPUT_RIGHT);

	switch (state)
	{
	case Main_State::STAY:


		input[Input_ID::LEVER].rock = true;
		input[Input_ID::LEFT].rock = true;
		input[Input_ID::MIDDLE].rock = true;
		input[Input_ID::RIGHT].rock = true;

		if (input[Input_ID::BET].active == true ||
			betSkip == true)
		{
			//レバーを押せるようにする
			input[Input_ID::LEVER].rock = false;
			//ベットボタンを押せないようにロックする
			input[Input_ID::BET].rock = true;

			state = Main_State::START;

		}

		break;
	case Main_State::START:

		StartUpdate();

		break;
	case Main_State::WAIT:
		WaitUpdate();

		break;
	case Main_State::SPEEN:
		SpeenUpdate();

		break;

	case Main_State::RESULT:
		ResultUpdate();

		break;
	case Main_State::RESET:
		ResetUpdate();
	}
}

void MainControl::Draw()
{
}

bool MainControl::GetAllPush()
{
	return (input[Input_ID::LEFT].active == true &&
			input[Input_ID::MIDDLE].active == true &&
			input[Input_ID::RIGHT].active == true);
}

bool MainControl::GetDontPush()
{
	return (input[Input_ID::LEFT].active == false&&
		input[Input_ID::MIDDLE].active == false &&
		input[Input_ID::RIGHT].active == false);
}

bool MainControl::CheckState(int id)
{
	return (state == id);
}

void MainControl::ResultCheck()
{
	state = Main_State::RESULT;
}

void MainControl::ResetCheck()
{
	state = Main_State::RESET;
}

void MainControl::SymbolAligned()
{
	medal->PayMedal(flag->GetPayMedal(flag->GetSymbol()));

}

void MainControl::StartUpdate()
{
	if (input[Input_ID::LEVER].active == true)
	{
		//ベットボタンを押せないようにロック
		input[Input_ID::BET].rock = true;

		betSkip = false;

		//メダルを投入
		//リプレイの場合は無視
		if (flag->GetPrevHit(flag->REPLAY) == false)
		{
			medal->BetMedal(BET_MAX);
		}


		//前の乱数をリセット

		//乱数抽選
		//通常ステージの場合

		if (!flag->GetHit())
		{
			flag->SetRand();
		}

		//回転数のカウントを増やす
		count++;

		

		//ステートをウェイトに移行
		state = Main_State::WAIT;

		input[Input_ID::LEVER].rock = true;
	}
}

void MainControl::WaitUpdate()
{
	waitTime += Time::DeltaTime();
	float rate = waitTime / WAIT_MAX;

	if (rate < 1.0f)
	{
		return;
	}

	input[Input_ID::LEFT].rock = false;
	input[Input_ID::MIDDLE].rock = false;
	input[Input_ID::RIGHT].rock = false;


	state = Main_State::SPEEN;
}

void MainControl::SpeenUpdate()
{

	reel->SetPush(0, input[Input_ID::LEFT].active);
	reel->SetPush(1, input[Input_ID::MIDDLE].active);
	reel->SetPush(2, input[Input_ID::RIGHT].active);

	int s = flag->GetSymbol();

	reel->SetSymbol(s);
}

void MainControl::ResultUpdate()
{
	input[Input_ID::BET].active = false;
	input[Input_ID::LEVER].active = false;
	input[Input_ID::BET].rock = false;
}

void MainControl::ResetUpdate()
{
	flag->SymbolReset();

	for (int i = 0; i < Input_ID::NUM; i++)
	{
		input[i].active = false;
	}

	state = Main_State::STAY;
}

void MainControl::SetInput(int index, int key)
{
	if (input[index].rock == true)
	{
		return;
	}


	input[index].active = CheckHitKey(key);

}