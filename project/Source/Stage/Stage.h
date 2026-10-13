#pragma once
#include "../object3D.h"

class Stage : public Object3D
{
public:
	Stage();
	~Stage();

	void Update()override;
	void Draw()override;

	void ObjectDraw()override;

private:
	int skyModel;
};