#pragma once
#include "../../Common/Object/objectBase.h"

class SubAManager :ObjectBase
{
public:
	SubAManager();
	~SubAManager();

	void Update()override;
	void Draw()override;
private:
};