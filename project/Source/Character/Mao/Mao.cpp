#include "Mao.h"

Mao::Mao()
{
	hModel = MV1LoadModel("data/model/mao/mao2.mv1");
	data.position = VZero;
}

Mao::~Mao()
{
}

void Mao::Update()
{
}

void Mao::Draw()
{
	MV1SetMatrix(hModel, Matrix());
	MV1DrawModel(hModel);
}
