#pragma once
#include "../../object3D.h"

class Mao :Object3D
{
public:
	Mao();
	~Mao();

	void Update()override;
	void Draw()override;

	const VECTOR3 GetPositon() { return data.position; }
private:
};