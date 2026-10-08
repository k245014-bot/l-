#pragma once
#include "../../objectBase.h"

class SubBManager :ObjectBase
{
public:
	SubBManager();
	~SubBManager();

	void Update()override;
	void Draw()override;
private:

	void CameraSet();
};