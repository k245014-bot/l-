#pragma once
#include "Base/MaoStateBase.h"

class MaoDanceState :public MaoStateBase
{
public:
	MaoDanceState();
	~MaoDanceState();

	void Update()override;
	void Draw()override;

	void Start()override;
	void Finish()override;
private:

};