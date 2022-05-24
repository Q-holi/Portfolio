#pragma once

struct Player
{
	ObImage*		image;
	ObRect*			col;
	GameObject*		firePos;	
	float			speed;
	float			hp;
	float			levelEXP;
	Vector2			dir;	//�÷��̾ �̵��ϴ� �������� ��ֶ����� �Ұ�
							//dir�� ����ϴ� ������ �밢������ �̵��ϴ� �����ӵ� �ӵ��� �����ϰ� �̵��ϱ� ����
	
	class Weapon*			weapon[6];

	Player();
	~Player();
	void Update();
	void Render();
	void TakeDamage(float damage);
	void GetLevelEXP(float levelEXP);
	void GetItem();
};

