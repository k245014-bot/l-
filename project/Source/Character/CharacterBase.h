#pragma once
#include "../object3D.h"

class CharacterBase : public Object3D
{
public:
	CharacterBase();
	~CharacterBase();

	virtual void Update()override;
	virtual void Draw()override;

	const VECTOR3 GetPositon() { return data.position; }
private:
};