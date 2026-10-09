#pragma once
#include "../object3D.h"

class CharacterBase : public Object3D
{
public:
	CharacterBase();
	~CharacterBase();

	void Update()override;
	void Draw()override;

	const VECTOR3 GetPositon() { return data.position; }
private:
};