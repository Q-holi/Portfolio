#pragma once
#define MAXshieldEnemy	5

//commit Test 
class Main : public Scene
{
private:
	Player*			player;
	ObImage*		bgMap;
	ShieldEnemy*	shieldEnemy[MAXshieldEnemy];

	float			monsterRespawnTime;


public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
