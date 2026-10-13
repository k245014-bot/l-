#pragma once
#include "../CharacterBase.h"

class Mao : public CharacterBase
{
public:
	Mao();
	~Mao();

	void Update()override;
	void Draw()override;

private:
};