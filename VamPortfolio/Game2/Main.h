#pragma once
#define MAXshieldEnemy	5

class Main : public Scene
{
private:
	Player*			player;
	ObImage*		bgMap;
	ShieldEnemy*	shieldEnemy[MAXshieldEnemy];
	Vector2			minVelocity;
	float			minVelocityDis;

	float			monsterRespawnTime;


public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
