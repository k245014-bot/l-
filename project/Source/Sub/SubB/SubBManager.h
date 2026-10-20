#pragma once
#include "../../Common/Object/objectBase.h"

//class Camera;
class Mao;
class ScreenManager;
class Stage;

class SubBManager :ObjectBase
{
public:
	SubBManager();
	~SubBManager();

	void Update()override;
	void Draw()override;
private:
	ScreenManager* cameraManager;
	Mao* mao;
	Stage* stage;

	//筐体画像
	int housingImage;
};