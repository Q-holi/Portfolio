#pragma once

class Weapon
{
public:
	ObImage*		image;
	ObImage*		attackImage[10];
	ObRect*			col[10];
	float			damage;
	int				level;
	float			attackTimer;
	float			attackTime;
	Vector2			velocity[10];
	int				attackCount;
	Weapon();
	~Weapon();

	virtual void Update();
	virtual void Render();
	void AttackTimeReset();
	void Attack(GameObject* firePos);

};

