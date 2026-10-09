#pragma once
#include "../../objectBase.h"

class Camera;
class Mao;

class SubBManager :ObjectBase
{
public:
	SubBManager();
	~SubBManager();

	void Update()override;
	void Draw()override;
private:
	Camera* camera;
	Mao* mao;
	void CameraSet();

	int m_3DTarget;
};