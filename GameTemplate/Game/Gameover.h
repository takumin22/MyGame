#pragma once
#include "Fade.h"
class Gameover
{
public:
	Gameover();
	~Gameover();
	void Update();
	void Draw();
private:
	Sprite m_oversprite; //ゲームオーバーのスプライト

};

