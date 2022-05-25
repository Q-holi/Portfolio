#include "stdafx.h"

LevelEXP::LevelEXP()
{
	col = new ObCircle();
	col->scale.x = 9.0f * 2.0f;
	col->scale.y = 12.0f * 2.0f;
	col->isFilled = false;
	col->visible = false;

	image = new ObImage(L"RED_EXP.png");
	image->scale = col->scale;
	image->SetParentRT(*col);
	image->visible = false;


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
	//col->Render();
}
