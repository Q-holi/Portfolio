#include "stdafx.h"

Sonic::Sonic()
{
	col = new ObRect();
	col->pivot = OFFSET_B;
	col->isFilled = false;
	col->scale = Vector2(160.0f / 4.0f, 60.0f) * 2.5f;
	col->SetWorldPosY(-256.0f);
	col->SetWorldPosX(-800.0f + 300.0f);

	run = new ObImage(L"run.bmp");
	run->scale = Vector2(192.0f / 4.0f, 60.0f) * 2.5f;
	run->pivot = OFFSET_B;
	run->maxFrame.x = 4;
	run->ChangeAnim(ANISTATE::LOOP, 0.1f);
	run->SetParentRT(*col);

	spin = new ObImage(L"spin.bmp");
	spin->scale = Vector2(240. / 5.0f, 48.0f) * 2.5f;
	spin->pivot = OFFSET_B;
	spin->maxFrame.x = 5;
	spin->ChangeAnim(ANISTATE::ONCE, 0.1f);
	spin->visible = false;
	spin->SetParentRT(*col);

	state = SONICSTATE::RUN;
	gravity = 0.0f;
	isDamaging = false;
}

void Sonic::Update()
{
	if (isDamaging)
	{
		damagingTime -= DELTA;
		run->color = Color(RANDOM->Float(0.5f,1.0f), 0.5f, 0.5f, 0.5f);
		spin->color = Color(RANDOM->Float(0.5f, 1.0f), 0.5f, 0.5f, 0.5f);





		if (damagingTime < 0.0f)
		{
			run->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
			spin->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
			isDamaging = false;
		}
	}

	col->MoveWorldPos(RIGHT * 200.0f * DELTA);
	CAM->position += RIGHT * 200.0f * DELTA;
	col->MoveWorldPos(DOWN * gravity * DELTA);
	gravity += 700.0f * DELTA;

	App.deltaScale += 0.1f * TIMER->GetDeltaTime();
	App.deltaScale = Util::saturate(App.deltaScale, 1.0f, 3.0f);

	if (state == SONICSTATE::RUN)
	{
		col->scale.y = 60.0f * 2.5f;

		//run to spin
		if (INPUT->KeyPress(VK_DOWN))
		{
			state = SONICSTATE::SPIN;
			spin->ChangeAnim(ANISTATE::ONCE, 0.1f);
			spin->visible = true;
			run->visible = false;
		}
		//run to jump
		if (INPUT->KeyPress(VK_SPACE))
		{
			state = SONICSTATE::JUMP;
			spin->ChangeAnim(ANISTATE::LOOP, 0.1f);
			spin->visible = true;
			run->visible = false;
			gravity = -700.0f;
			doubleJump = false;
		}
	}

	else if (state == SONICSTATE::SPIN)
	{
		col->scale.y = 48.0f * 2.5f;
		//spin to run
		if (INPUT->KeyUp(VK_DOWN))
		{
			state = SONICSTATE::RUN;
			spin->visible = false;
			run->visible = true;
		}
		//spin to jump
		if (INPUT->KeyPress(VK_SPACE))
		{
			state = SONICSTATE::JUMP;
			spin->ChangeAnim(ANISTATE::LOOP, 0.1f);
			gravity = -700.0f;
			doubleJump = false;
		}
	}

	else
	{
		if (INPUT->KeyDown(VK_SPACE) and not doubleJump)
		{
			gravity = -700.0f;
			doubleJump = true;
		}

		//jump to run
	}

	col->Update();
	spin->Update();
	run->Update();
}

void Sonic::Render()
{
	col->Render();
	run->Render();
	spin->Render();
}
