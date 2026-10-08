#pragma once
#include "../objectBase.h"

class Camera :ObjectBase
{
public:
	Camera();
	~Camera();

	void Update()override;
	void Draw()override;
private:
};