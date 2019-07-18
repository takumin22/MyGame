#pragma once
#include "Fade.h"
class Gameover
{
public:
	Gameover();
	~Gameover();
	enum Overstate {
		State_Continue,
		State_Title
	};
	void Update();
	void Draw();
	void OverClear();
	bool Getflag()
	{
		return Continueflag;
	}
	bool Gettitleflag()
	{
		return TitleFlag;
	}
private:
	Font m_font;
	wchar_t mojimoji[256];
	Sprite m_oversprite; //ゲームオーバーのスプライト
	Sprite m_yajisprite;
	CVector3 m_yajipos = { -300.0f,-80.0f,0.0f };				//矢印のポジション
	bool flag = false;
	bool Continueflag = false;
	bool TitleFlag = false;
	Overstate m_overstate = State_Continue;
};

