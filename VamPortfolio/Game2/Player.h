#pragma once

struct Player
{
	ObImage*		image;
	ObRect*			col;
	GameObject*		firePos;	
	ObRect*			levelBar;	
	float			speed;
	float			hp;
	float			levelEXP;
	Vector2			dir;	//플레이어가 이동하는 방향으로 노멀라이즈 할것
							//dir을 사용하는 이유는 대각선으로 이동하는 움직임도 속도를 동일하게 이동하기 위해
	
	vector<class Weapon*>		weapon;


	Player();
	~Player();
	void Update();
	void Render();
	void TakeDamage(float damage);
	void GetLevelEXP(float levelEXP);
	void GetItem();
};

