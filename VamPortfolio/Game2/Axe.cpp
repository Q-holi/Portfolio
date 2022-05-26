#include "stdafx.h"

Axe::Axe()
{
	for (int i = 0; i < 3; i++) {
		col[i] = new ObRect();
		col[i]->scale = Vector2(16.0f, 18.0f) * 3.0f;
		col[i]->isFilled = false;
		col[i]->visible = false;
		col[i]->SetWorldPos(Vector2(0.0f, 0.0f));

		attackImage[i] = new ObImage(L"Axe.png");
		attackImage[i]->scale = Vector2(16.0f, 18.0f) * 3.0f;
		attackImage[i]->SetParentRT(*col[i]);
		attackImage[i]->isFilled = false;
		attackImage[i]->visible = false;

		gravity[i] =  -700.0f;
	}
	damage = 50.0f;
	level = 1;
	attackTime = 0.8f;
	attackTimer = attackTime;
	attackCount = 0;

	weaponType = WEAPONTYPE::AXE;
}

Axe::~Axe()
{
}

void Axe::Update()
{
}

void Axe::Render()
{
}
