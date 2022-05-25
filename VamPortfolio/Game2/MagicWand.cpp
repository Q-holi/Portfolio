#include "stdafx.h"

MagicWand::MagicWand()
{
	for (int i = 0; i < 10; i++) {
		col[i] = new ObRect();
		col[i]->scale = Vector2(25.0f, 12.0f) * 2.0f;
		col[i]->isFilled = false;
		col[i]->visible = false;
		col[i]->SetWorldPos(Vector2(0.0f, 0.0f));

		attackImage[i] = new ObImage(L"MagicAttack.png");
		attackImage[i]->scale = Vector2(25.0f, 12.0f) * 2.0f;
		attackImage[i]->SetParentRT(*col[i]);
		//velocity[i] = Vector2(0.0f, 0.0f);
	}
	
	damage = 10.0f;
	level = 1;
	attackTime = 0.2f;
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

