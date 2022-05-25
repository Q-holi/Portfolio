#pragma once
class MagicWand : public Weapon
{
public:

	MagicWand();
	~MagicWand();

	void Update()override;
	void Render()override;
};

