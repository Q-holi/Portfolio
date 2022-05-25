#include "stdafx.h"

LevelEXP::LevelEXP()
{
	col = new ObCircle();
	col->scale.x = 9.0f * 2.0f;
	col->scale.y = 12.0f * 2.0f;
	col->visible = false;

	image = new ObImage(L"EXP.png");
	image->scale = col->scale;
	image->SetParentRT(*col);
	image->visible = false;
	image->color = Color(0.5f, 0.5f, 0.5f, 1.0f);

	exp = 100.0f;
}

LevelEXP::~LevelEXP()
{

}

void LevelEXP::Update()
{
	image->Update();
	col->Update();
}

void LevelEXP::Render()
{
	image->Render();
	col->Render();
}
