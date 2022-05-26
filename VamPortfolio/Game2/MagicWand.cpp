#include "stdafx.h"

MagicWand::MagicWand()
{
	for (int i = 0; i < 20; i++) {
		col.push_back(new ObRect());
		attackImage.push_back(new ObImage(L"MagicAttack.png"));
		velocity.push_back(Vector2());
	}
	for (int j = 0; j < col.size(); j++) {
		col[j]->scale = Vector2(25.0f, 12.0f) * 2.0f;
		col[j]->isFilled = false;
		col[j]->visible = false;
		col[j]->SetWorldPos(Vector2(0.0f, 0.0f));

		attackImage[j]->scale = Vector2(25.0f, 12.0f) * 2.0f;
		attackImage[j]->SetParentRT(*col[j]);
		attackImage[j]->visible = false;
	}
	damage = 10.0f;
	level = 1;
	attackTime = 0.2f;
	attackTimer = attackTime;
	attackCount = 0;
	weaponType = WEAPONTYPE::MAGICWAND;
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

