#pragma once
#include "../../../State/StateBase.h"
class Mao;

class MaoStateBase : public StateBase
{
public:
	MaoStateBase();
	~MaoStateBase();

	virtual void Update()override;
	virtual void Draw()override;

	virtual void Start()override;
	virtual void Finish()override;

protected:
	Mao* mao;
};