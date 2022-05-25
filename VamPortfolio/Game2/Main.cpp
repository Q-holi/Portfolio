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

	monsterRespawnTime = 5.0f;


	minVelocity = Vector2(9999.0f, 9999.0f);
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
	player->weapon[0]->attackTimer -= DELTA; // 플레이어 무기 1번의 공격시간

	minVelocityDis = FLT_MAX;
	for (int i = 0; i < MAXshieldEnemy; i++) {
		if (monsterRespawnTime >= 2.0f) {
			if (!shieldEnemy[i]->col->visible and !shieldEnemy[i]->image->visible) {
				monsterRespawnTime = 0.0f;
				shieldEnemy[i]->Respawn();
				cout << i << "번째 몬스터 생성 : X->" << shieldEnemy[i]->col->GetWorldPos().x << "|| y->" << shieldEnemy[i]->col->GetWorldPos().y << endl;
			}
		}
		//if (minVelocity.Length() > (player->col->GetWorldPos() - shieldEnemy[i]->col->GetWorldPos()).Length()) {
		//	minVelocity = player->col->GetWorldPos() - shieldEnemy[i]->col->GetWorldPos();
		//}

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

	bgMap->Update();
	for (int i = 0; i < MAXshieldEnemy; i++)
		shieldEnemy[i]->Update();

	player->Update();
}

void Main::LateUpdate()
{
	for (int i = 0; i < MAXshieldEnemy; i++) {
		for (int j = 0; j < 10; j++) {
			if (shieldEnemy[i]->col->Intersect(player->weapon[0]->col[j]) and player->weapon[0]->col[j]->visible and shieldEnemy[i]->col->visible) {
				player->weapon[0]->col[j]->visible = false;
				shieldEnemy[i]->TakeDamage(player->weapon[0]->damage);
			}
		}
	}
}
void Main::Render()
{
	bgMap->Render();
	for (int i = 0; i < MAXshieldEnemy; i++)
		shieldEnemy[i]->Render();

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
