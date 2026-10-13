#pragma once
#include "../../objectBase.h"

//class Camera;
class Mao;
class CameraManager;
class Stage;

class SubBManager :ObjectBase
{
public:
	SubBManager();
	~SubBManager();

	void Update()override;
	void Draw()override;
private:
	CameraManager* cameraManager;
	Mao* mao;
	Stage* stage;

	//筐体画像
	int housingImage;
};