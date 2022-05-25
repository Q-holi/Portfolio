#pragma once
class PlayerInven
{
public :
	ObImage* playerInven;
	ObImage* playerInvenItem;

	PlayerInven();
	~PlayerInven();

	void Update();
	void Render();
};

