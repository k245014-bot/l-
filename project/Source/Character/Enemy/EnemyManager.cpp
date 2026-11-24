#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager::EnemyManager()
{
	enemy = new Enemy();
	enemy->CreateEnemy(VECTOR3(250, 90, -6000));
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
}

void EnemyManager::Draw()
{

}

void EnemyManager::CreateEnemy(const VECTOR3& position)
{

}

void EnemyManager::ObjectDraw()
{
	enemy->ObjectDraw();
}