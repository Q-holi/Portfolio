#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	player = new Player();

	for (int i = 0; i < MAXshieldEnemy; i++)
		shieldEnemy[i] = new ShieldEnemy();

	bgMap = new ObImage(L"BackGroundMap.png");
	bgMap->scale = Vector2(2048.0f, 2048.0f);
	bgMap->space = SPACE::SCREEN;

	for (int i = 0; i < 6; i++) {
		playerInven[i] = new PlayerInven();
		playerInven[i]->playerInven->SetLocalPos(Vector2(-App.GetHalfWidth() + i * 50.0f, App.GetHalfHeight()));
	}

	monsterRespawnTime = 5.0f;
	minVelocity = Vector2(9999.0f, 9999.0f);

	testTime = 10.0f;
}

void Main::Release()
{

}

//D3D->GetDC()->OMSetBlendState(GameObject::blendStateOff, NULL, 0xFF);
//D3D->GetDC()->OMSetBlendState(GameObject::blendStateOn, NULL, 0xFF);
void Main::Update()
{
	bgMap->uv.x = 0.0f + CAM->position.x / bgMap->scale.x;
	bgMap->uv.z = 1.0f + CAM->position.x / bgMap->scale.x;

	bgMap->uv.y = 0.0f - CAM->position.y / bgMap->scale.y;
	bgMap->uv.w = 1.0f - CAM->position.y / bgMap->scale.y;

	CAM->position = player->col->GetWorldPos();

	monsterRespawnTime += DELTA;//몬스터 스폰 시간
	testTime -= DELTA;

	for(int i =0; i<player->weapon.size();i++)
		player->weapon[i]->attackTimer -= DELTA; // 플레이어 각각의무기  공격시간



	minVelocityDis = FLT_MAX;
	for (int i = 0; i < MAXshieldEnemy; i++) {
		if (monsterRespawnTime >= 2.0f) {
			if (!shieldEnemy[i]->col->visible and !shieldEnemy[i]->image->visible) {
				monsterRespawnTime = 0.0f;
				shieldEnemy[i]->Respawn();
				//cout << i << "번째 몬스터 생성 : X->" << shieldEnemy[i]->col->GetWorldPos().x << "|| y->" << shieldEnemy[i]->col->GetWorldPos().y << endl;
			}
		}

		//플레이어의 방향으로 몬스터 움직이게 하기
		Vector2 velocity = player->col->GetWorldPos() - shieldEnemy[i]->col->GetWorldPos();
		velocity.Normalize();
		shieldEnemy[i]->MoveMonster(velocity);

		if (shieldEnemy[i]->col->visible and shieldEnemy[i]->image->visible) {
			//if (minVelocity.Length() > (player->col->GetWorldPos() - shieldEnemy[i]->col->GetWorldPos()).Length()) {
			if (minVelocityDis > (player->col->GetWorldPos() - shieldEnemy[i]->col->GetWorldPos()).Length()) {
				minVelocity = player->col->GetWorldPos() - shieldEnemy[i]->col->GetWorldPos();
				minVelocityDis = minVelocity.Length();
			}
		}
	}
	//플레이어 아이템 공격 시간 계산
	if (minVelocityDis != FLT_MAX)
	{
		if (player->weapon[0]->attackTimer < 0.0f) {
			Vector2 dir = minVelocity;
			player->firePos->rotation = Util::DirToRadian(dir);
			player->weapon[0]->Weapon::Attack(player->firePos);
		}
	}

	if (player->weapon[1]->attackTimer < 0.0f) {
		player->weapon[1]->Weapon::Attack(player->firePos);
	}

	if (testTime < 0.0f) {
		cout << "성경 소환" << endl;
		player->firePos->Update();
		player->weapon[2]->Weapon::Attack(player->col);
		testTime = 20.0f;
	}

	bgMap->Update();
	for (int i = 0; i < MAXshieldEnemy; i++)
		shieldEnemy[i]->Update();

	player->Update();
	for (int i = 0; i < 6; i++) {
		playerInven[i]->Update();
	}
	for (int i = 0; i < levelExp.size(); i++) {
		levelExp[i]->Update();
	}
}

void Main::LateUpdate()
{
	for (int i = 0; i < MAXshieldEnemy; i++) {
		for (int j = 0; j < player->weapon[0]->col.size(); j++) {
			if (shieldEnemy[i]->col->Intersect(player->weapon[0]->col[j]) and player->weapon[0]->col[j]->visible and shieldEnemy[i]->col->visible) {
				player->weapon[0]->col[j]->visible = false;
				player->weapon[0]->attackImage[j]->visible = false;
				if (shieldEnemy[i]->TakeDamage(player->weapon[0]->damage)) {
					levelExp.push_back(new LevelEXP(shieldEnemy[i]->col->GetWorldPos()));
					cout << "겅험치 생성" << endl;
				}
			}
		}
		for (int j = 0; j < player->weapon[1]->col.size(); j++) {
			if (shieldEnemy[i]->col->Intersect(player->weapon[1]->col[j]) and player->weapon[1]->col[j]->visible and shieldEnemy[i]->col->visible) {
				player->weapon[1]->col[j]->visible = false;
				player->weapon[1]->attackImage[j]->visible = false;
				if (shieldEnemy[i]->TakeDamage(player->weapon[1]->damage)) {
					levelExp.push_back(new LevelEXP(shieldEnemy[i]->col->GetWorldPos()));
					cout << "겅험치 생성" << endl;
				}
			}
		}
	}


	for (int i = 0; i < levelExp.size(); i++) {
		levelExp[i]->col->visible = true;
		levelExp[i]->image->visible = true;
	}
	//for (int i = 0; levelExp.size(); i++) {
	//	if (player->col->Intersect(levelExp[i]->col) and levelExp[i]->col->visible and levelExp[i]->image->visible) {
	//		cout << "겅험치 드랍" << endl;
	//		player->GetLevelEXP(levelExp[i]->exp);
	//		levelExp[i]->~LevelEXP();
	//		levelExp.erase(levelExp.begin() + i);
	//	}
	//}
	PlayerLevelUP();
}
void Main::Render()
{
	bgMap->Render();
	for (int i = 0; i < MAXshieldEnemy; i++)
		shieldEnemy[i]->Render();

	player->Render();
	for (int i = 0; i < 6; i++) {
		playerInven[i]->Render();
	}

	for (int i = 0; i < levelExp.size(); i++) {
		levelExp[i]->Render();
	}
}

void Main::ResizeScreen()
{

}

void Main::PlayerLevelUP()
{
	for (int i = 0; i < player->weapon.size(); i++) {
		if (player->weapon[i]->weaponType == WEAPONTYPE::AXE) {
			playerInven[i]->playerInvenItem->uv.x = 0.0;
			playerInven[i]->playerInvenItem->uv.z = 1.0 / 3.0f;
			playerInven[i]->playerInvenItem->visible = true;
		}
		if (player->weapon[i]->weaponType == WEAPONTYPE::MAGICWAND) {
			playerInven[i]->playerInvenItem->uv.x = 1.0 / 3.0f;
			playerInven[i]->playerInvenItem->uv.z = 1.0 / 3.0f * 2.0f;
			playerInven[i]->playerInvenItem->visible = true;
		}
		if (player->weapon[i]->weaponType == WEAPONTYPE::KINGBIBLE) {
			playerInven[i]->playerInvenItem->uv.x = 1.0 / 3.0f * 2.0f;
			playerInven[i]->playerInvenItem->uv.z = 1.0 / 3.0f * 3.0f;
			playerInven[i]->playerInvenItem->visible = true;
		}

	}

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"VampireSurvivors");
	App.SetInstance(instance);
	App.InitWidthHeight(1536.0f, 972.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}
