#pragma once
class ShieldEnemy : public Enemy
{
public :
	ObRect*		col;
	ObImage*	image;
	float		hp;
	float		damage;
	float		speed;

	ShieldEnemy();
	~ShieldEnemy();

	void Update()override;
	void Render()override;
	void Respawn()override;

	void TakeDamage(float damage);
	void MoveMonster(Vector2 velocity);
	void DestroyMoster();
};

