#include "Enemy.h"

Enemy::Enemy()
{
	LoadModel("enemy/yoroikun.mv1");
	data.position = VZero;

	animation = new AnimationManager(hModel);
	
	LoadAnim(animData.idle, "enemy/Motion/enemyIdle.mv1");
	SetAnimation(0, animData.idle, 20.0f, true);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	animation->Play(motionId, playMotion, motionSpeed, isMotionLoop);
}

void Enemy::Draw()
{
}

void Enemy::CreateEnemy(const VECTOR3& position)
{
	SetPosition(position);
}