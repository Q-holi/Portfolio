#include "stdafx.h"

Weapon::Weapon()
{

}

Weapon::~Weapon()
{
}

void Weapon::Update()
{
	if (weaponType == WEAPONTYPE::MAGICWAND) {
		for (int i = 0; i < 10; i++) {
			if (col[i]->visible) {
				col[i]->MoveWorldPos(velocity[i] * DELTA);
			}
			col[i]->Update();
			attackImage[i]->Update();
		}
	}
	else if (weaponType == WEAPONTYPE::AXE) {
		for (int i = 0; i < 3; i++) {
			if (col[i]->visible) {
				col[i]->MoveWorldPos(velocity[i] * DELTA);
			}
			col[i]->Update();
			attackImage[i]->Update();
		}
	}
}

void Weapon::Render()
{
	if (weaponType == WEAPONTYPE::MAGICWAND) {
		for (int i = 0; i < 10; i++) {
			if (col[i]->visible) {
				col[i]->MoveWorldPos(velocity[i] * DELTA);
			}
			//col[i]->Render();
			attackImage[i]->Render();
		}
	}
	else if (weaponType == WEAPONTYPE::AXE) {
		for (int i = 0; i < 3; i++) {
			if (col[i]->visible) {
				col[i]->MoveWorldPos(DOWN * gravity[i] * DELTA);
				col[i]->rotation += DELTA *4.0f;
				gravity[i] += 700.0f * DELTA;
			}
			//col[i]->Render();
			attackImage[i]->Render();
		}
	}
}

void Weapon::AttackTimeReset()
{
	attackTimer = attackTime;
}

void Weapon::Attack(GameObject* firePos)
{
	if (weaponType == WEAPONTYPE::MAGICWAND) {
		col[attackCount]->visible = true;
		attackImage[attackCount]->visible = true;
		col[attackCount]->SetWorldPos(firePos->GetWorldPos());
		velocity[attackCount] = firePos->GetRight() * -1.0f * 300.0f;
		col[attackCount]->rotation = Util::DirToRadian(velocity[attackCount]);

		if (attackCount >= 9)
			attackCount = 0;
		else
			attackCount++;
	}
	else if (weaponType == WEAPONTYPE::AXE) {
		col[attackCount]->visible = true;
		attackImage[attackCount]->visible = true;
		col[attackCount]->SetWorldPos(firePos->GetWorldPos());
		gravity[attackCount] = -700.0f;

		if (attackCount >= 2)
			attackCount = 0;
		else
			attackCount++;
	}

	AttackTimeReset();

}
