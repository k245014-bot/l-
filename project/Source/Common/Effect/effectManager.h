#pragma once
#include "../Object/objectBase.h"

class EffectManager :public ObjectBase
{
public:
	EffectManager();
	~EffectManager();
	void Update()override;
	void Draw()override;

private:
	
};

