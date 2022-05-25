#include "stdafx.h"

ShieldEnemy::ShieldEnemy()
{
	col = new ObRect();
	col->scale = Vector2(90.0f / 2.0f, 49.0f) * 2.0f;
	col->isFilled = false;
	col->visible = false;
	col->SetWorldPos(Vector2(FLT_MAX, FLT_MAX));

	image = new ObImage(L"ShieldEnemy.png");
	image->scale = Vector2(90.0 / 2.0f, 49.0f) * 2.0f;
	image->maxFrame.x = 2;
	image->SetParentRT(*col);
	image->visible = false;


	speed = 100.0f;
	hp = 100.0f;
	//col->SetWorldPos(Vector2(90.0f, 49.0f));
}

ShieldEnemy::~ShieldEnemy()
{

}

void ShieldEnemy::Update()
{

	col->Update();
	image->Update();
	levelEXP->Update();

}

void ShieldEnemy::Render()
{

	//col->Render();
	image->Render();
	levelEXP->Render();
}

void ShieldEnemy::Respawn()
{
	// 각 posX posY의 고정 혹은 랜덤 범위 를 주기 위해서 입니다.
	//bool변수 3개를 이용해서 각 카메라 범위 밖에 위치에서 생성
	bool posRespawn = RANDOM->Int();
	bool xposRespawn = RANDOM->Int();
	bool yposRespawn = RANDOM->Int();

	if (posRespawn) {
		if (xposRespawn)
			col->SetWorldPosX(CAM->position.x + App.GetHalfWidth() * 1.2f);
		else
			col->SetWorldPosX(CAM->position.x - App.GetHalfWidth() * 1.2f);

		col->SetWorldPosY(RANDOM->Float(CAM->position.y - App.GetHalfHeight() * 1.2f, CAM->position.y + App.GetHalfHeight() * 1.2f));
	}
	else {
		if (yposRespawn)
			col->SetWorldPosY(CAM->position.y + App.GetHalfHeight() * 1.2f);
		else
			col->SetWorldPosY(CAM->position.y - App.GetHalfHeight() * 1.2f);

		col->SetWorldPosX(RANDOM->Float(CAM->position.x - App.GetHalfWidth() * 1.2f, CAM->position.x + App.GetHalfWidth() * 1.2f));
	}
	col->visible = true;
	image->visible = true;
	col->Update();
	image->Update();
}

void ShieldEnemy::TakeDamage(float damage)
{
	if (hp < 0.0f) {
		DestroyMoster();
	}
	else {
		cout << "피격당함" << endl;
		hp -= damage;
	}
		

}

void ShieldEnemy::MoveMonster(Vector2 velocity)
{
	//플레이어 이동방향에 따른 몬스터에 바라보는 방향 
	if (velocity.x < 0)
		image->reverseLR = false;
	else
		image->reverseLR = true;

	image->ChangeAnim(ANISTATE::LOOP, 0.2f);
	col->MoveWorldPos(velocity * DELTA * speed);
	//플레이어의 방향으로 움지이기
}

void ShieldEnemy::DestroyMoster()
{
	levelEXP->col->SetWorldPos(col->GetWorldPos());
	col->visible = false;
	image->visible = false;
	levelEXP->col->visible = true;
	levelEXP->image->visible = true;
	hp = 100.0f;

}
