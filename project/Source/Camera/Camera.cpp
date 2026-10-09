#include "Camera.h"
#include "../Mao/Mao.h"

Camera::Camera()
{
	mao = nullptr/*FindGameObject<Mao>()*/;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	VECTOR3 offset = VECTOR3(0.0f, 400.0f , 300.0f);
	offset = offset * MGetRotX(data.rotation.x) * MGetRotY(data.rotation.y + DX_PI_F);
	VECTOR3 lookPosition = mao->GetPositon();

	SetCameraPositionAndTarget_UpVecY(
		lookPosition + offset,
		lookPosition + VECTOR3(0.0f, 200.0f, 0.0f));
}

void Camera::Draw()
{
}

void Camera::Set(Mao* _mao)
{
	mao = _mao;
}
