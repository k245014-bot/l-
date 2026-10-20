#pragma once
#include "../Common/Object/object3D.h"

class Mao;

class Camera :public Object3D
{
public:
	Camera();
	~Camera();

	void Update()override;
	void Draw()override;

	void Set(Mao* _mao);
	void CameraMove();
	void NormalMove(float _speed);
	void Move(VECTOR3 _vector, float _speed);

private:
	Mao* mao;
	//ÉJÉÅÉâÇÃà íuí≤êÆ
	VECTOR3 CAMERA_OFFSET = VECTOR3(0.0f, 200.0f, -500.0f);
};