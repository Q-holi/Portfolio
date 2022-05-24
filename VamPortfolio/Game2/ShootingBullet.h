#pragma once
class ShootingBullet
{
public:
	ObRect*		col;
	Vector2     fireDir;
	float		scalar;  //�ӷ�
	bool		fire;
	float       damage;

	ShootingBullet();
	~ShootingBullet();

	virtual bool Shoot(Vector2 firePos, Vector2 fireDir, float fireForce);
	virtual void Update();
	virtual void Render();
};

