#include "Wall.h"

Wall::Wall(VECTOR3 _pos)
{
	hModel = MV1LoadModel("data/model/sky/Stage00_sky.mv1");
	//data.position = _pos;
	//data.scale = VECTOR3(30.0f,30.0f,30.0f);
}

Wall::~Wall()
{
}

void Wall::Update()
{
}

void Wall::Draw()
{
}

void Wall::ObjectDraw()
{
	Object3D::ObjectDraw();
}
