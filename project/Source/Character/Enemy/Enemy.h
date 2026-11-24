#pragma once
#include "../CharacterBase.h"

class Enemy : public CharacterBase
{
public:
	Enemy();
	~Enemy();

	void Update()override;
	void Draw()override;

	void CreateEnemy(const VECTOR3& position);

private:
	struct AnimationData
	{
		int idle;
	};
	AnimationData animData;
};