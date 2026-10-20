#pragma once
#include "../../../Common/Object/object3D.h"
class Camera;
class Mao;
class Stage;

class ScreenManager :Object3D
{
public:
	ScreenManager();
	~ScreenManager();

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