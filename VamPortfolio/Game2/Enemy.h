#pragma once
class Enemy
{
public:
	class LevelEXP* levelEXP;

	Enemy();
	~Enemy();

	virtual void Update();
	virtual void Render();
	virtual void Respawn();
};
