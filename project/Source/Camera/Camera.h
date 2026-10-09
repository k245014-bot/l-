#pragma once
#include "../object3D.h"

class Mao;

class Camera :Object3D
{
public:
	Camera();
	~Camera();

	void Update()override;
	void Draw()override;

	void Set(Mao* _mao);
private:
	Mao* mao;
};