#pragma once
#define MAXshieldEnemy	10

class Main : public Scene
{
private:
	vector<class LevelEXP*>		levelExp;
	Player*						player;//사용자가 플레이할 캐릭터
	ObImage*					bgMap;//배경맵 
	PlayerInven*				playerInven[6];//좌측 상단에 캐릭터 아이템 창
	ShieldEnemy*				shieldEnemy[MAXshieldEnemy];//소환할 몬스터 개채수
	Vector2						minVelocity;
	float						minVelocityDis;
	float						monsterRespawnTime;//몬스터 생성 속도
	float						testTime;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void PlayerLevelUP();
};
