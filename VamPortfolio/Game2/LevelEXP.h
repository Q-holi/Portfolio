#pragma once

class LevelEXP
{
public:
	ObImage*	image;
	ObCircle*	col;
	float		exp;

	LevelEXP(Vector2 creatPos);
	~LevelEXP();

	void Update();
	void Render();

};

