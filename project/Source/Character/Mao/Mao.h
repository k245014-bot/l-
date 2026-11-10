#pragma once
#include "../CharacterBase.h"
#include "MaoStateData.h"

class StateManager;

class Mao : public CharacterBase
{
public:
	friend class MaoDanceState;
	friend class MaoDanceAtkState;

	Mao();
	~Mao();

	void Update()override;
	void Draw()override;

	void ImGuiDraw();
private:
	StateManager* state;
	const std::string fileName = "mao/mao2.mv1";

	StateData stateData;
	struct AnimationData
	{
		int dance;
		int attack;
	};
	AnimationData animData;
	
};
