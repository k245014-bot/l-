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
	VECTOR3 forward;
	// カメラの前方向を計算
	forward.x = sinf(data.rotation.y) * cosf(data.rotation.x);
	forward.y = -sinf(data.rotation.x);
	forward.z = cosf(data.rotation.y) * cosf(data.rotation.x);

	// 注視点を計算
	VECTOR3 target = data.position + forward * 100.0f;
	SetCameraPositionAndTarget_UpVecY(data.position, target);
}

void  Camera::NormalMove(float _speed)
{
	Move(VECTOR3(0, 0, -1), _speed);
}

void  Camera::Move(const VECTOR3& _vector, const float& _speed)
{
	data.position += _vector * MGetRotY(data.rotation.y) * _speed;
}

void  Camera::SetPosition(const VECTOR3& _pos)
{ 
	data.position = _pos; 
}