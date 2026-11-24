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
	//スクリーンで更新してる
	void CameraMove();
	void NormalMove(float _speed);
	void Move(const VECTOR3& _vector, const float& _speed);
	void SetPosition(const VECTOR3& _pos);
	void SetRotation(const VECTOR3& _rot) { data.rotation = _rot; }
private:
	Mao* mao;
	//カメラの初期位置
	VECTOR3 CAMERA_OFFSET = VECTOR3(0.0f, 100.0f, -6500.0f);
};