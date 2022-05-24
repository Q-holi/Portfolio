#pragma once

struct Floor
{
	ObImage*	img;
	ObRect*		col;
	bool        isvisible;
};

class Main : public Scene
{
private:
	ObImage*	rock[4];
	Floor		floor[8];
	Sonic*		sonic;
	ObImage *	bg1;
	ObImage *	bg2;

	ObRect *	Menu;
	float		bgmScale;
	float		gunScale;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

};
