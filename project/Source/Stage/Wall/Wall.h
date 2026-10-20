#pragma once
#include "../../object3D.h"

class Wall : public Object3D
{
public:
	Wall(VECTOR3 _pos);
	~Wall();

	void Update()override;
	void Draw()override;

	void ObjectDraw()override;

private:
	
};