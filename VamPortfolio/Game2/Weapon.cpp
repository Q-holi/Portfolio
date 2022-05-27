#include "stdafx.h"

Weapon::Weapon()
{

}

Weapon::~Weapon()
{
}

void Weapon::Update()
{

	if (weaponType == WEAPONTYPE::MAGICWAND) {
		for (int i = 0; i < col.size(); i++) {
			if (col[i]->visible) {
				col[i]->MoveWorldPos(velocity[i] * DELTA);
			}
			col[i]->Update();
			attackImage[i]->Update();
		}
	}
	else if (weaponType == WEAPONTYPE::AXE) {
		for (int i = 0; i < col.size(); i++) {
			if (col[i]->visible) {
				col[i]->MoveWorldPos(DOWN * gravity[i] * DELTA);
				col[i]->rotation += DELTA * 4.0f;
				gravity[i] += 700.0f * DELTA;
			}
			col[i]->Update();
			attackImage[i]->Update();
		}
	}
	else if (weaponType == WEAPONTYPE::KINGBIBLE) {
		attackTimer -= DELTA;
		if (attackTimer >= 0.0f) {
			for (int i = 0; i < col.size(); i++) {
				string str = to_string(i) + "bible";
				ImGui::SliderAngle(str.c_str(), &col[i]->rotation2);
				if (col[i]->visible) {
					col[i]->rotation2 += 200.0f * ToRadian * DELTA;
					col[i]->rotation -= 200.0f * ToRadian * DELTA;
				}
				col[i]->Update();
				attackImage[i]->Update();
			}
		}
		else {
			for (int i = 0; i < col.size(); i++) {
				col[i]->visible = false;
				attackImage[i]->visible = false;
				//col[i]->Update();
				//attackImage[i]->Update();
			}


		}
	}
}

void Weapon::Render()
{
	if (weaponType == WEAPONTYPE::MAGICWAND) {
		for (int i = 0; i < col.size(); i++) {
			if (col[i]->visible) {
				attackImage[i]->Render();
			}
			//col[i]->Render();

		}
	}
	else if (weaponType == WEAPONTYPE::AXE) {
		for (int i = 0; i < col.size(); i++) {
			if (col[i]->visible) {
				attackImage[i]->Render();
			}
			//col[i]->Render();
		}
	}
	else if (weaponType == WEAPONTYPE::KINGBIBLE) {
		for (int i = 0; i < col.size(); i++) {
			if (col[i]->visible) {
				//col[i]->Render();
				attackImage[i]->Render();
			}

		}
	}
}

void Weapon::AttackTimeReset()
{
	attackTimer = attackTime;
}

void Weapon::Attack(GameObject* firePos)
{
	if (weaponType == WEAPONTYPE::MAGICWAND) {
		if (attackCount >= col.size()) {
			attackCount = 0;
			return;
		}
		col[attackCount]->visible = true;
		attackImage[attackCount]->visible = true;
		col[attackCount]->SetWorldPos(firePos->GetWorldPos());
		velocity[attackCount] = firePos->GetRight() * -1.0f * 300.0f;
		col[attackCount]->rotation = Util::DirToRadian(velocity[attackCount]);
		attackCount++;
	}
	else if (weaponType == WEAPONTYPE::AXE) {
		if (attackCount >= col.size()) {
			attackCount = 0;
			return;
		}
		col[attackCount]->visible = true;
		attackImage[attackCount]->visible = true;
		col[attackCount]->SetWorldPos(firePos->GetWorldPos());
		gravity[attackCount] = -700.0f;
		attackCount++;
	}
	else if (weaponType == WEAPONTYPE::KINGBIBLE) {
		cout << "성경 생성 시작" << endl;
		for (int i = 0; i < col.size(); i++) {
			firePos->Update();
			cout << i + 1 << "번 책 생성완료" << endl;
			col[i]->SetParentRT(*firePos);
			col[i]->SetLocalPosX(cosf((360.0f / col.size()) * (i + 1) * ToRadian) * 250.0f);
			col[i]->SetLocalPosY(sinf((360.0f / col.size()) * (i + 1) * ToRadian) * 250.0f);
			col[i]->visible = true;
			attackImage[i]->visible = true;
		}
		cout << "성경 생성 완료" << endl;
	}

	AttackTimeReset();

}
