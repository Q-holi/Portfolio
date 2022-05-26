#include "stdafx.h"

PlayerInven::PlayerInven()
{
	playerInven = new ObImage(L"InventoryEmpty.png");
	playerInven->scale = Vector2(28.0f, 28.0f) * 2.0f;
	playerInven->pivot = OFFSET_LT;
	playerInven->space = SPACE::SCREEN;

	playerInvenItem = new ObImage(L"Items.png");
	playerInvenItem->scale = Vector2(28.0f , 28.0f) * 2.0f;
	playerInvenItem->pivot = OFFSET_LT;
	playerInvenItem->space = SPACE::SCREEN;
	playerInvenItem->frame.x = 3;
	playerInvenItem->visible = false;
	playerInvenItem->SetParentRT(*playerInven);
}

PlayerInven::~PlayerInven()
{
}

void PlayerInven::Update()
{

	playerInven->Update();
	playerInvenItem->Update();
}

void PlayerInven::Render()
{

	playerInven->Render();
	playerInvenItem->Render();
}

