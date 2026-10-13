#include "mainControl.h"
#include "reel.h"

MainControl::MainControl()
{
	SetDrawOrder(110);
	reel = new Reel(this);
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
