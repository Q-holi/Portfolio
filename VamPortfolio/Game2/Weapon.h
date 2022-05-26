#pragma once
enum class WEAPONTYPE {
	AXE,
	MAGICWAND,
	KINGBIBLE
};

class Weapon
{
public:
	//ObImage*			attackImage[10];
	///ObRect*			col[10];
	//Vector2			velocity[10];
	//float				gravity[10];
	vector<ObImage*>	attackImage;
	vector<ObRect*>		col;
	vector<Vector2>		velocity;
	vector<float>		gravity;

	float				damage;
	int					level;
	float				attackTimer;
	float				attackTime;
	int					attackCount;
	WEAPONTYPE			weaponType;
	Weapon();
	~Weapon();

	virtual void Update();
	virtual void Render();
	void AttackTimeReset();
	void Attack(GameObject* firePos);

};

