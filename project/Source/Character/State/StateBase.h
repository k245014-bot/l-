#pragma once
#include "../../Common/Object/object3D.h"

class StateBase : public Object3D
{
public:
	StateBase() = default;
	~StateBase() = default;

	virtual void Update()override {};
	virtual void Draw()override {};

	virtual void Start() {};
	virtual void Finish() {};
protected:

};