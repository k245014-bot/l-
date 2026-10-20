#include "Camera.h"
#include "../Character/Mao/Mao.h"

Camera::Camera()
{
	mao = nullptr/*FindGameObject<Mao>()*/;

	data.position = CAMERA_OFFSET;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	
}

void Camera::Draw()
{
}

void Camera::Set(Mao* _mao)
{
	mao = _mao;
}

void Camera::CameraMove()
{
	/*VECTOR3 offset = VECTOR3(0.0f, 200.0f, -500.0f);
	VECTOR3 lookPosition = mao->GetPositon();*/

	SetCameraPositionAndTarget_UpVecY(data.position, data.position + VECTOR3(0.0f, 0.0f, 100.0f));
}

void  Camera::NormalMove(float _speed)
{
	Move(VECTOR3(0, 0, -1), _speed);
}

void  Camera::Move(VECTOR3 _vector, float _speed)
{
	data.position += _vector * MGetRotY(data.rotation.y) * _speed;
}
