#pragma once
#include "../objectBase.h"

class Reel;

class MainControl :public ObjectBase
{
public:
	MainControl();
	~MainControl();
	void Update()override;
	void Draw()override;

private:

	Reel* reel;
};
