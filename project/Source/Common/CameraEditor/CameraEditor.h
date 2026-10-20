#pragma once
#include "../Object/objectBase.h"
#include "../Input/inputManager.h"

class Camera;
class InputManager;
class CameraEditor:public ObjectBase
{
public:
	CameraEditor();
	~CameraEditor();

	void Update()override;
	void Draw()override;

private:
	Camera* camera;
	InputManager* input;
	void ImGuiDraw();
	void CameraControl();
};