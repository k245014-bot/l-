#include "Camera.h"
#include "../Character/Mao/Mao.h"

Camera::Camera()
{
	mao = nullptr/*FindGameObject<Mao>()*/;
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
	VECTOR3 offset = VECTOR3(0.0f, 200.0f, -500.0f);
	VECTOR3 lookPosition = mao->GetPositon();

	SetCameraPositionAndTarget_UpVecY(lookPosition + offset, lookPosition + VECTOR3(0.0f, 100.0f, 0.0f));
}
