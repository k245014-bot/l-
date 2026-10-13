#include "mainControl.h"
#include "reel.h"
#include "flagLottery.h"
#include "creditMedal.h"

MainControl::MainControl()
{
	SetDrawOrder(110);
	reel = new Reel(this);
	flag = new FlagLottery;
	count = 0;
	state = Main_State::STAY;
}

MainControl::~MainControl()
{
}

void MainControl::Update()
{
}

void MainControl::Draw()
{
}

bool MainControl::GetAllPush()
{
	return false;
}

bool MainControl::GetDontPush()
{
	return false;
}

bool MainControl::CheckState(int id)
{
	return false;
}

void MainControl::ResultCheck()
{
}

void MainControl::ResetCheck()
{
}

void MainControl::SymbolAligned()
{
}

void MainControl::BetUpdate()
{
}

void MainControl::SpeenUpdate()
{
}

void MainControl::WaitUpdate()
{
}

void MainControl::ResultUpdate()
{
}

void MainControl::ResetUpdate()
{
}
