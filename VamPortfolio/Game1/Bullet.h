#pragma once
#define BULLETMAX 5

struct Bullet
{
	ObLine		arrow;
	ObCircle    arrowPet;

	//��º���
	Vector2     fireDir;
	float		scalar;  //�ӷ�

	//�߷º���
	float		gravity;  //�߷�


	Bullet();
	bool Shoot(Vector2 firePos, Vector2 fireDir,float fireForce);
	void Update();
	void LateUpdate();
	void Render();
};
