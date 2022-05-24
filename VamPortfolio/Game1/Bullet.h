#pragma once
#define BULLETMAX 5

struct Bullet
{
	ObLine		arrow;
	ObCircle    arrowPet;

	//ฝ๎ดยบคลอ
	Vector2     fireDir;
	float		scalar;  //ผำทย

	//ม฿ทยบคลอ
	float		gravity;  //ม฿ทย


	Bullet();
	bool Shoot(Vector2 firePos, Vector2 fireDir,float fireForce);
	void Update();
	void LateUpdate();
	void Render();
};
