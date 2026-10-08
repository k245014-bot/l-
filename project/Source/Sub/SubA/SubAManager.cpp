#include "SubAManager.h"
#include "../SubB/SubBManager.h"

SubAManager::SubAManager()
{
	new SubBManager;
}

SubAManager::~SubAManager()
{
}

void SubAManager::Update()
{
}

void SubAManager::Draw()
{
}
