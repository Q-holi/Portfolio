#pragma once
class Enemy
{
public:

	Enemy();
	~Enemy();

	virtual void Update();
	virtual void Render();
	virtual void Respawn();
};
