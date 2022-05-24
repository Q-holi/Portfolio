#include "stdafx.h"
#include "Main.h"
void Main::Init()
{
	bg1 = new ObImage(L"Oven1.png");
	bg1->scale = Vector2(569.0f, 320.0f)* 2.5f;
	bg1->space = SPACE::SCREEN;

	bg2 = new ObImage(L"Oven2.png");
	bg2->scale = Vector2(862.0f, 320.0f) * 2.5f;
	bg2->space = SPACE::SCREEN;

	Menu = new ObRect();
	Menu->scale = Vector2(100, 50);
	Menu->space = SPACE::SCREEN;
	Menu->SetWorldPos(Vector2(-700.0f,400.0f));
	Menu->pivot = OFFSET_LT;
	

	sonic = new Sonic();
	
	//스핀으로 피해야하는값
	-130.0f;

	//점프로 피해야되는값
	-256.0f;

	for (int i = 0; i < 4; i++)
	{
		rock[i] = new ObImage(L"rock.bmp");
		rock[i]->scale = Vector2(60.0f, 60.0f)*2.5f;
		rock[i]->pivot = OFFSET_B;
		rock[i]->SetWorldPos(Vector2(800.0f + i*600.0f, -130.0f * RANDOM->Int(1,2)));
		rock[i]->collider = COLLIDER::CIRCLE;
	}

	for (int i = 0; i < 8; i++)
	{
		floor[i].img = new ObImage(L"floor.bmp");
		floor[i].img->scale = Vector2(79.0f, 48.0f) * 3.0f;
		floor[i].img->pivot = OFFSET_LT;

		floor[i].col = new ObRect();
		floor[i].col->scale = Vector2(79.0f, 5.0f) * 3.0f;
		floor[i].col->pivot = OFFSET_LT;
		floor[i].col->isFilled = false;
		floor[i].col->color = Color(1, 0, 0, 1);

		floor[i].col->SetWorldPos(Vector2(-800.0f + (i* 79.0f * 3.0f),-400.0f + 48.0f * 3.0f));
		floor[i].img->SetParentRT(*floor[i].col);
		floor[i].isvisible = true;
	}
	SOUND->AddSound("bgm.wav", "BGM", true);
	SOUND->AddSound("gun.wav", "GUN");
	SOUND->Play("BGM");

	bgmScale = 1.0f;
	gunScale = 1.0f;
}

void Main::Release()
{
	SafeDelete(sonic);
	for (int i = 0; i < 8; i++)
	{
		SafeDelete(floor[i].col);
		SafeDelete(floor[i].img);
	}
	for (int i = 0; i < 4; i++)
	{
		SafeDelete(rock[i]);
	}
}


void Main::Update()
{
	if (ImGui::SliderFloat("AppSoundScale",&App.soundScale,0.0f,1.0f))
	{
		SOUND->SetMasterVolume();
	}
	if (ImGui::Button("BGMPLAY"))
	{
		SOUND->Play("BGM");
	}
	ImGui::SameLine();
	if (ImGui::Button("BGMSTOP"))
	{
		SOUND->Stop("BGM");
	}
	ImGui::SameLine();
	if (ImGui::Button("BGMPAUSE"))
	{
		SOUND->Pause("BGM");
	}
	ImGui::SameLine();
	if (ImGui::Button("BGMRESUME"))
	{
		SOUND->Resume("BGM");
	}
	if (ImGui::SliderFloat("BGMSCALE", &bgmScale, 0.0f, 1.0f))
	{
		SOUND->SetVolume("BGM", bgmScale);
	}

	if (ImGui::Button("GUNPLAY"))
	{
		SOUND->Stop("GUN");
		SOUND->Play("GUN");
	}
	ImGui::SameLine();
	if (ImGui::Button("GUNSTOP"))
	{
		SOUND->Stop("GUN");
	}
	ImGui::SameLine();
	if (ImGui::Button("GUNPAUSE"))
	{
		SOUND->Pause("GUN");
	}
	ImGui::SameLine();
	if (ImGui::Button("GUNRESUME"))
	{
		SOUND->Resume("GUN");
	}
	if (ImGui::SliderFloat("GUNSCALE", &gunScale, 0.0f, 1.0f))
	{
		SOUND->SetVolume("GUN", gunScale);
	}

	//배경이 왼쪽으로 초당 100씩 움직임
	bg1->uv.x += DELTA / bg1->scale.x*50.0f;
	bg1->uv.z += DELTA / bg1->scale.x*50.0f;

	bg2->uv.x += DELTA / bg2->scale.x * 100.0f;
	bg2->uv.z += DELTA / bg2->scale.x * 100.0f;

	ImGui::SliderFloat("DeltaScale", &App.deltaScale, 0.001f, 100.0f);
	


	sonic->Update();
	for (int i = 0; i < 8; i++)
	{
		if (sonic->col->GetWorldPos().x - floor[i].col->GetWorldPos().x > 600.0f)
		{
			floor[i].col->MoveWorldPos(Vector2((8.0f * 79.0f * 3.0f), 0.0f));

			if (RANDOM->Int(0, 10) == 1)
			{
				floor[i].isvisible = false;
			}
			else
			{
				floor[i].isvisible = true;
			}

		}

		floor[i].col->Update();
		floor[i].img->Update();
	}
	for (int i = 0; i < 4; i++)
	{
		if (sonic->col->GetWorldPos().x - rock[i]->GetWorldPos().x > 600.0f)
		{
			rock[i]->MoveWorldPos(Vector2(2400.0f, 0.0f));
			rock[i]->SetLocalPosY(-130.0f * RANDOM->Int(1, 2));
			if (RANDOM->Int(0, 1) == 1)
			{
				rock[i]->visible = false;
			}
			else
			{
				rock[i]->visible = true;
			}
		}
		rock[i]->Update();
	}
	bg1->Update();
	bg2->Update();
	Menu->Update();
}

void Main::LateUpdate()
{
	//만약 바닥과 소닉이 충돌중이라면
	for (int i = 0; i < 8; i++)
	{
		if (not floor[i].isvisible) continue;

		if (floor[i].col->Intersect(sonic->col->GetWorldPos()))
		{
			sonic->col->SetWorldPosY(-256.0f);
			sonic->gravity = 0.0f;
			//jump to run
			if (sonic->state == SONICSTATE::JUMP)
			{
				sonic->state = SONICSTATE::RUN;
				sonic->spin->visible = false;
				sonic->run->visible = true;
			}
			sonic->col->Update();
			sonic->run->Update();
			sonic->spin->Update();
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (not rock[i]->visible) continue;
		if (rock[i]->Intersect(sonic->col))
		{
			sonic->SetDamage();
		}
	}
	//
	//bg2->Update();

	//if (Menu->Intersect(INPUT->GetMouseScreenPos()))
	if (Menu->IntersectScreenMouse(INPUT->GetMouseScreenPos()))
	{
		Menu->color.x = 1.0f;
	}
	else
	{
		Menu->color.x = 0.5f;
	}

}



void Main::Render()
{

	bg1->Render();
	bg2->Render();
	Menu->Render();

	sonic->Render();
	for (int i = 0; i < 8; i++)
	{
		if (not floor[i].isvisible) continue;

		floor[i].img->Render();
		floor[i].col->Render();
	}
	for (int i = 0; i < 4; i++)
	{
		rock[i]->Render();
	}
	
}

void Main::ResizeScreen()
{
}


int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game1");
	App.SetInstance(instance);
	App.InitWidthHeight(1400.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}
