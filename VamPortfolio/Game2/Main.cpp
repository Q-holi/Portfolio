#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	player = new Player();

	for (int i = 0; i < MAXshieldEnemy; i++) {
		shieldEnemy[i] = new ShieldEnemy();
	}
	

	bgMap = new ObImage(L"BackGroundMap.png");
	bgMap->scale = Vector2(2048.0f, 2048.0f);
	bgMap->space = SPACE::SCREEN;

	monsterRespawnTime = 5.0f;
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
	for (int i = 0; i < MAXshieldEnemy; i++) {
		if (shieldEnemy[i]->hp > 0.0f) {
			if (monsterRespawnTime >= 2.0f) {
				shieldEnemy[i]->Respawn();
				monsterRespawnTime = 0.0f;
			}

			//플레이어의 방향으로 몬스터 움직이게 하기
			Vector2 velocity = player->col->GetWorldPos() - shieldEnemy[i]->col->GetWorldPos();
			velocity.Normalize();
			shieldEnemy[i]->MoveMonster(velocity);
		}


		//플레이어 아이템 공격 시간 계산

	}
	//player->weapon[0]->attackTimer -= DELTA;
	//if (player->weapon[0]->attackTimer < 0.0f) {
	//	Vector2 dir = player->col->GetWorldPos() - shieldEnemy[i]->col->GetWorldPos();
	//	player->firePos->rotation = Util::DirToRadian(dir);
	//	player->weapon[0]->Weapon::Attack(player->firePos);
	//}
	

	bgMap->Update();
	for (int i = 0; i < MAXshieldEnemy; i++) {
		shieldEnemy[i]->Update();
	}
	player->Update();
}

void Main::LateUpdate()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < MAXshieldEnemy; j++) {
			if (player->weapon[0]->col[i]->Intersect(shieldEnemy[j]->col)) {
				player->weapon[0]->col[i]->visible = false;
				player->weapon[0]->attackImage[i]->visible = false;
			}
		}

	}
}
void Main::Render()
{
	bgMap->Render();
	for (int i = 0; i < MAXshieldEnemy; i++) {
		shieldEnemy[i]->Render();
	}
	player->Render();
}

void Main::ResizeScreen()
{

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
