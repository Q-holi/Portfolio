#pragma once

class LevelEXP
{
public:
	ObImage*	image;
	ObCircle*	col;
	float		exp;

	LevelEXP();
	~LevelEXP();

	void Update();
	void Render();
};

