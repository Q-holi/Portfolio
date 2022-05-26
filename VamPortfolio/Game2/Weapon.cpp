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
		for (int i = 0; i < col.size(); i++) {
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
		for (int i = 0; i < col.size(); i++) {
			if (col[i]->visible) {
				col[i]->MoveWorldPos(velocity[i] * DELTA);
			}
			//col[i]->Render();
			attackImage[i]->Render();
		}
	}
	else if (weaponType == WEAPONTYPE::AXE) {
		for (int i = 0; i < col.size(); i++) {
			if (col[i]->visible) {
				col[i]->MoveWorldPos(DOWN * gravity[i] * DELTA);
				col[i]->rotation += DELTA * 4.0f;
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
		if (attackCount >= col.size()) {
			attackCount = 0;
			return;
		}
		col[attackCount]->visible = true;
		attackImage[attackCount]->visible = true;
		col[attackCount]->SetWorldPos(firePos->GetWorldPos());
		velocity[attackCount] = firePos->GetRight() * -1.0f * 300.0f;
		col[attackCount]->rotation = Util::DirToRadian(velocity[attackCount]);
		attackCount++;
	}
	else if (weaponType == WEAPONTYPE::AXE) {
		if (attackCount >= col.size()) {
			attackCount = 0;
			return;
		}
		col[attackCount]->visible = true;
		attackImage[attackCount]->visible = true;
		col[attackCount]->SetWorldPos(firePos->GetWorldPos());
		gravity[attackCount] = -700.0f;
		attackCount++;
	}

	AttackTimeReset();

}
