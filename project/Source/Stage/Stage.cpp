#include "Stage.h"
#include "Wall/Wall.h"

Stage::Stage()
{
	wall = new Wall(VECTOR3(0, 0, 800.0f));
	hModel = MV1LoadModel("data/model/stage/zimen.mv1");
	skyModel = MV1LoadModel("data/model/sky/Stage00_sky.mv1");
	wallModel = MV1LoadModel("data/model/stage/Wall/Wall1.mv1");

	wallPosition = VZero;
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

	wall->ObjectDraw();
}
