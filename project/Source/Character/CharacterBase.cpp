#include "CharacterBase.h"

CharacterBase::CharacterBase()
{
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::Update()
{
}

void CharacterBase::Draw()
{
	MV1SetMatrix(hModel, Matrix());
	MV1DrawModel(hModel);
}
