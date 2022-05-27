#include "stdafx.h"

Player::Player()
{
	col = new ObRect();
	col->scale = Vector2(116.0f / 3.0f, 33.0f) * 2.0f;
	col->SetLocalPos(Vector2(0.0f, 0.0f));
	col->isFilled = false;

	image = new ObImage(L"Player1.png");
	image->scale = Vector2(116.0f / 3.0f, 33.0f) * 2.0f;
	image->maxFrame.x = 4;
	image->SetParentRT(*col);

	firePos = new GameObject();
	firePos->SetParentRT(*col);

	levelEXP = 0.0f;

	speed = 200.0f;
	for (int i = 0; i < 3; i++) {
		weapon.push_back(new Weapon);
	}
	weapon[0] = new MagicWand();
	weapon[1] = new Axe();
	weapon[2] = new KingBible();
}

Player::~Player()
{
	SafeDelete(col);
	SafeDelete(image);
}

void Player::Update()
{
	dir = Vector2(0.0f, 0.0f);

	if (INPUT->KeyPress(VK_RIGHT))
	{
		image->ChangeAnim(ANISTATE::LOOP, 0.1f);
		image->reverseLR = false;
		dir.x = 1.0f;
	}
	else if (INPUT->KeyPress(VK_LEFT)) {
		image->ChangeAnim(ANISTATE::LOOP, 0.1f);
		image->reverseLR = true;
		dir.x = -1.0f;
	}

	if (INPUT->KeyPress(VK_UP))
		dir.y = 1.0f;
	else if (INPUT->KeyPress(VK_DOWN))
		dir.y = -1.0f;



	dir.Normalize();
	col->MoveWorldPos(dir * speed * DELTA);
	col->Update();
	image->Update();
	firePos->Update();
	for (int i = 0; i < weapon.size(); i++) {
		weapon[i]->Weapon::Update();
	}
	
}

void Player::Render()
{

	//col->Render();
	image->Render();
	for (int i = 0; i < weapon.size(); i++) {
		weapon[i]->Weapon::Render();
	}
}

void Player::TakeDamage(float damage)
{
	if (hp < 0.0f) {
		//플레이어 사망 하는 시점
	}
	else {
		hp -= damage;
		//피격 받았을 때 이미지 색상 조금 변경 (RED)
	}
}

void Player::GetLevelEXP(float levelEXP)
{
	this->levelEXP += levelEXP;
}

void Player::GetItem()
{

}

