#pragma once
#include "Base/MaoStateBase.h"

class MaoDanceAtkState :public MaoStateBase
{
public:
	MaoDanceAtkState();
	~MaoDanceAtkState();

	void Update()override;
	void Draw()override;

	void Start()override;
	void Finish()override;
private:

};