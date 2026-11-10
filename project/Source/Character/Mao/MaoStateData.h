#pragma once
#include "State/MaoDanceState.h"
#include "State/MaoDanceAtkState.h"
class StateBase;

struct StateData
{
	StateBase* dance;
	StateBase* danceAtk;
};