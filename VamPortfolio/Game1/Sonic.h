#pragma once

enum class SONICSTATE
{
	RUN,
	SPIN,
	JUMP
};

struct Sonic
{
	Sonic();

	ObImage * spin;
	ObImage * run;
	ObRect * col;
	SONICSTATE  state;
	float		gravity;
	bool		isDamaging;
	float		damagingTime;
	bool		doubleJump;

	void Update();
	void Render();
	void SetDamage()
	{
		isDamaging = true;
		damagingTime = 0.5f;
	}
};

