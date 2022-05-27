#include "stdafx.h"

KingBible::KingBible()
{
	for (int i = 0; i < 3; i++) {
		col.push_back(new ObRect());
		attackImage.push_back(new ObImage(L"KingBible.png"));
	}
	for (int j = 0; j < col.size(); j++) {
		col[j]->scale = Vector2(10.0f, 15.0f) * 3.0f;
		col[j]->isFilled = false;
		col[j]->visible = false;
		col[j]->SetWorldPos(Vector2(0.0f, 0.0f));
		col[j]->rotation = col[j]->rotation2 = 0.0f;

		attackImage[j]->scale = Vector2(10.0f, 15.0f) * 3.0f;
		attackImage[j]->SetParentRT(*col[j]);
		attackImage[j]->visible = false;
	}

	damage = 25.0f;
	level = 1;
	attackTime = 10.0f;

	attackTimer = attackTime;
	attackCount = 0;

	weaponType = WEAPONTYPE::KINGBIBLE;
}

KingBible::~KingBible()
{

}

void KingBible::Update()
{

}

void KingBible::Render()
{

}
