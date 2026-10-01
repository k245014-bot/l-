#pragma once
#include "../Library/GameObject.h"

class ObjectBase: public GameObject
{
public:
	ObjectBase();
	~ObjectBase();
	virtual void Update()override {};
	virtual void Draw()override {};

	inline void SetResourceKeep(const bool& resource) { resourceKeep = resource; }

protected:
	bool resourceKeep;


};

