#include "mainControl.h"
#include "reel.h"
#include "flagLottery.h"
#include "creditMedal.h"

MainControl::MainControl()
{
	SetDrawOrder(110);
	reel = new Reel(this);
	flag = new FlagLottery;
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
