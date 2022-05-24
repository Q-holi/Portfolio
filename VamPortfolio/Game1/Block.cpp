#include "stdafx.h"

Block::Block()
{
	life = RANDOM->Int(1, 3);
	block = new ObRect();

	if (RANDOM->Int(0, 9) == 4)
	{
		item = RANDOM->Int(PLAYERSPEED, PLAYERWIDTH);
	}
	else
	{
		item = NONE;
	}

}

void Block::Update()
{
	if (life == 0 && item != NONE)
	{
		block->MoveWorldPos(DOWN * 100.0f * DELTA);
	}


	block->Update();
}

void Block::Render()
{
	if (life < 0)
	{
		return;
	}
	if (life == 0 && item == NONE)
	{
		return;
	}

	switch (life)
	{
	case 1:
		block->color = Color(1.0f, 0.5f, 0.5f, 1);
		break;
	case 2:
		block->color = Color(0.5f, 1.0f, 0.5f, 1);
		break;
	case 3:
		block->color = Color(0.5f, 0.5f, 1.0f, 1);
		break;
	}
	

	block->Render();
}
