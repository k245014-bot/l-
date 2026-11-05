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
	const std::string fileName = "mao/mao2.mv1";

	struct AnimationData
	{
		int dance;
	};
};