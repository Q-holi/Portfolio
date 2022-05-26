#include "stdafx.h"

Axe::Axe()
{
	for (int i = 0; i < 3; i++) {
		col.push_back(new ObRect());
		attackImage.push_back(new ObImage(L"Axe.png"));
		velocity.push_back(Vector2());
		gravity.push_back(float(-700.0f));
	}
	for (int j = 0; j < col.size(); j++) {
		col[j]->scale = Vector2(16.0f, 18.0f) * 3.0f;
		col[j]->isFilled = false;
		col[j]->visible = false;
		col[j]->SetWorldPos(Vector2(0.0f, 0.0f));

		attackImage[j]->scale = Vector2(16.0f, 18.0f) * 3.0f;
		attackImage[j]->SetParentRT(*col[j]);
		attackImage[j]->visible = false;
	}

	damage = 50.0f;
	level = 1;
	attackTime = 1.5f;
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
