#include "stdafx.h"

Weapon::Weapon()
{

}

Weapon::~Weapon()
{
}

void Weapon::Update()
{
	for (int i = 0; i < 10; i++) {
		col[i]->MoveWorldPos(velocity[i] * DELTA);
		col[i]->Update();
		attackImage[i]->Update();
	}
}

void Weapon::Render()
{
	for (int i = 0; i < 10; i++) {
		col[i]->Render();
		attackImage[i]->Render();
	}
}

void Weapon::AttackTimeReset()
{
	attackTimer = attackTime;
}

void Weapon::Attack(GameObject* firePos)
{
	col[attackCount]->visible = true;
	attackImage[attackCount]->visible = true;
	col[attackCount]->SetWorldPos(firePos->GetWorldPos());
	velocity[attackCount] = firePos->GetRight() * -1.0f * 300.0f;
	col[attackCount]->rotation = Util::DirToRadian(velocity[attackCount]);

	if (attackCount >= 9)
		attackCount = 0;
	else
		attackCount++;
	
	AttackTimeReset();

}
