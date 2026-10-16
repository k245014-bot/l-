#pragma once
#include "../object3D.h"

class Camera;
class Mao;
class Stage;

class CameraManager :Object3D
{
public:
	CameraManager();
	~CameraManager();

	void Update()override;
	void Draw()override;

	void CameraDrawScreen();
private:
	Camera* camera;
	Mao* mao;
	Stage* stage;

	void DrawObjects();
	int m_3DTarget;
};