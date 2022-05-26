#include "stdafx.h"

LevelEXP::LevelEXP(Vector2 creatPos)
{
	col = new ObCircle();
	col->scale.x = 9.0f * 2.0f;
	col->scale.y = 12.0f * 2.0f;
	col->SetWorldPos(creatPos);
	col->isFilled = false;
	col->visible = false;

	image = new ObImage(L"RED_EXP.png");
	image->scale = col->scale;
	image->SetParentRT(*col);
	image->visible = false;

	exp = 100.0f;

	col->Update();
	image->Update();
	image->Render();

}

LevelEXP::~LevelEXP()
{
	SafeDelete(col);
	SafeDelete(image);
}

void LevelEXP::Update()
{
	col->Update();
	image->Update();
}

void LevelEXP::Render()
{
	image->Render();
}
