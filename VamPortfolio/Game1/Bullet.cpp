#include "stdafx.h"

Bullet::Bullet()
{
	//화살
	arrow.SetWorldPos(Vector2(2000, 2000));
	arrow.scale.x = 30.0f;
	arrow.scale.y = 30.0f;
	arrow.visible = false;
	//arrow.axis = true;

	arrowPet.SetLocalPos(Vector2(30, 30));
	arrowPet.scale.x = 15.0f;
	arrowPet.scale.y = 15.0f;
	arrowPet.visible = false;
	arrowPet.SetParentRT(arrow);
}

bool Bullet::Shoot(Vector2 firePos, Vector2 fireDir, float fireForce)
{
	if (!arrow.visible)
	{
		arrow.visible = true;
		arrowPet.visible = true;

		//발사시점에서 플레이어 위치를 받아온다.
		arrow.SetWorldPos(firePos);
		this->fireDir = fireDir;
		this->scalar = fireForce * 6.0f;
		//
		arrowPet.rotation2 = 0.0f;
		//            0~150
		gravity = 0.0f;
		return true;
	}
	return false;
}

void Bullet::Update()
{
	if (not arrow.visible) return;
	//초당 속도는 100증가
	gravity += 700.0f * DELTA;
	//cout << scalar << endl;
	//                             v1   + v2
	Vector2 Velocity = fireDir * scalar + DOWN * gravity;
	//Vector2 Velocity = fireDir * scalar ;
	arrow.MoveWorldPos(Velocity * DELTA);
	arrow.rotation = Util::DirToRadian(Velocity);




	arrowPet.rotation2 += 360.0f * ToRadian* DELTA;

	arrow.Update();
	arrowPet.Update();

	
}

void Bullet::LateUpdate()
{
	//윗벽과 부딪혔을때
	if (arrow.GetWorldPos().y >= App.GetHeight() * 0.5 + CAM->position.y)
	{
		/*arrow.visible = false;
		arrowPet.visible = false;*/
		fireDir.y *= -1.0f;
		gravity *= -1.0f;

		scalar *= 0.9f;
		gravity *= 0.9f;
		arrow.SetWorldPosY(App.GetHeight() * 0.5f + CAM->position.y);
	}
	//아래벽과 부딪혔을때
	if (arrow.GetWorldPos().y <= -App.GetHeight() * 0.5 + CAM->position.y)
	{
		/*arrow.visible = false;
		arrowPet.visible = false;*/
		fireDir.y *= -1.0f;
		gravity *= -1.0f;

		scalar *= 0.9f;
		gravity *= 0.9f;
		arrow.SetWorldPosY(-App.GetHeight() * 0.5f + CAM->position.y);
	}

	if (arrow.GetWorldPos().x >= App.GetWidth() * 0.5 + CAM->position.x)
	{
		/*arrow.visible = false;
		arrowPet.visible = false;*/
		fireDir.x *= -1.0f;

		scalar *= 0.9f;
		arrow.SetWorldPosX(App.GetWidth() * 0.5f + CAM->position.x);
	}
	if (arrow.GetWorldPos().x <= -App.GetWidth() * 0.5 + CAM->position.x)
	{
		/*arrow.visible = false;
		arrowPet.visible = false;*/
		fireDir.x *= -1.0f;

		scalar *= 0.9f;
		arrow.SetWorldPosX(-App.GetWidth() * 0.5f + CAM->position.x);
	}

}

void Bullet::Render()
{
	arrow.Render();
	arrowPet.Render();
}
