#pragma once
#include "Sprite.h"
class Player;
class HP
{
public:
	HP();
	~HP();
	void Draw();
	void Update();
	void SetDamageCount(int k)
	{
		DamageCount = k;
	}
private:
	Sprite m_hp;
	Sprite m_hp2;
	Sprite m_hp3;
	Sprite m_hp4;
	CVector3 m_hppos = { 300.0f,300.0f,0.0f };
	CVector3 m_hppos2 = { 400.0f,300.0f,0.0f };
	CVector3 m_hppos3 = { 500.0f,300.0f,0.0f };
	CVector3 m_hppos4 = { 600.0f,300.0f,0.0f };
	Player* m_player = nullptr;
	int DamageCount = 0;

};

