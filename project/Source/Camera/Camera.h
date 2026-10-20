#pragma once
#include "../Common/Object/object3D.h"

class Mao;

class Camera :Object3D
{
public:
	Camera();
	~Camera();

	void Update()override;
	void Draw()override;

	void Set(Mao* _mao);
	void CameraMove();
private:
	Mao* mao;
};