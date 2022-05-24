#include "stdafx.h"

MagicWand::MagicWand()
{
	for (int i = 0; i < 10; i++) {
		col[i] = new ObRect();
		col[i]->scale = Vector2(25.0f, 12.0f) * 2.0f;
		col[i]->isFilled = false;
		col[i]->visible = false;

		attackImage[i] = new ObImage(L"MagicAttack.png");
		attackImage[i]->scale = Vector2(25.0f, 12.0f) * 2.0f;
		attackImage[i]->SetParentRT(*col[i]);
	}
	
	damage = 10.0f;
	level = 1;
	attackTime = 0.5f;
	attackTimer = attackTime;
	attackCount = 0;
}

MagicWand::~MagicWand()
{
}

void MagicWand::Update()
{

}

void MagicWand::Render()
{
}

