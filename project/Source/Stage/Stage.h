#pragma once
#include "../Common/Object/object3D.h"

class Wall;

class Stage : public Object3D
{
public:
	Stage();
	~Stage();

	void Update()override;
	void Draw()override;

	void ObjectDraw()override;

private:
	Wall* wall;
	int skyModel;
	int wallModel;
	VECTOR3 wallPosition;
};