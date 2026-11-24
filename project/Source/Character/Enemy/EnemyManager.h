#pragma once
#include "../../Common/Object/objectBase.h"

class Enemy;

class EnemyManager :public ObjectBase
{
public:
	EnemyManager();
	~EnemyManager();

	void Update()override;
	void Draw()override;

	void ObjectDraw();
	void CreateEnemy(const VECTOR3& position);
private:
	Enemy* enemy;
};