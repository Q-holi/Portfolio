#include "stdafx.h"

ShieldEnemy::ShieldEnemy()
{
	col = new ObRect();
	col->scale = Vector2(90.0f / 2.0f, 49.0f) * 2.0f;
	col->isFilled = false;
	col->visible = false;

	image = new ObImage(L"ShieldEnemy.png");
	image->scale = Vector2(90.0/2.0f, 49.0f) * 2.0f;
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
}

void ShieldEnemy::Render()
{

	col->Render();
	image->Render();
}

void ShieldEnemy::Respawn()
{
	//�� p
	// osX posY�� ���� Ȥ�� ���� ���� �� �ֱ� ���ؼ� �Դϴ�.
	//bool���� 3���� �̿��ؼ� �� ī�޶� ���� �ۿ� ��ġ���� ����
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
		if(yposRespawn)
			col->SetWorldPosY(CAM->position.y + App.GetHalfHeight() * 1.2f);
		else
			col->SetWorldPosY(CAM->position.y - App.GetHalfHeight() * 1.2f);

		col->SetWorldPosX(RANDOM->Float(CAM->position.x - App.GetHalfWidth() * 1.2f, CAM->position.x + App.GetHalfWidth() * 1.2f));
	}
	col->visible = true;
	image->visible = true;
}

void ShieldEnemy::TakeDamage(float damage)
{
	if (hp < 0.0f and !levelEXP->col->visible) {
		levelEXP->col->SetWorldPos(col->GetWorldPos());
		col->visible = false;
		image->visible = false;
		levelEXP->col->visible = true;
		levelEXP->image->visible = true;
	}
	else 
		hp -= damage;
	
}

void ShieldEnemy::MoveMonster(Vector2 velocity)
{
	//�÷��̾� �̵����⿡ ���� ���Ϳ� �ٶ󺸴� ���� 
	if (velocity.x < 0)
		image->reverseLR = false;
	else
		image->reverseLR = true;
	
	image->ChangeAnim(ANISTATE::LOOP, 0.2f);
	col->MoveWorldPos(velocity * DELTA * speed);
	//�÷��̾��� �������� �����̱�
}
