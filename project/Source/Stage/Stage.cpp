#include "Stage.h"

Stage::Stage()
{
	hModel = MV1LoadModel("data/model/stage/zimen.mv1");
	skyModel = MV1LoadModel("data/model/sky/Stage00_sky.mv1");
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	
}

void Stage::ObjectDraw()
{
	Object3D::ObjectDraw();
	if (skyModel > 0)
	{
		MV1SetMatrix(skyModel, Matrix());
		MV1DrawModel(skyModel);
	}
}
