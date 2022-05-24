#include "stdafx.h"

Enemy::Enemy()
{
	levelEXP = new LevelEXP();
}

Enemy::~Enemy()
{
	SafeDelete(levelEXP);
}

void Enemy::Update()
{
	levelEXP->Update();
}

void Enemy::Render()
{
	levelEXP->Render();
}

void Enemy::Respawn()
{
}
