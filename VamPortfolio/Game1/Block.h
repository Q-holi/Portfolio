#pragma once
enum ITEMTYPE
{
	NONE,
	PLAYERSPEED,
	BALLSPEED,
	PLAYERWIDTH,
};
class Block
{
private:
	

public:
	int			item;
	int			life;
	ObRect*		block;
	Block();
	void Update();
	void Render();

};

