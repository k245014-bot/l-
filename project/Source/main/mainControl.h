#pragma once
#include "../objectBase.h"

class MainControl :public ObjectBase
{
public:
	MainControl();
	~MainControl();
	void Update()override;
	void Draw()override;

private:

};
