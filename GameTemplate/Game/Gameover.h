#pragma once
#include "Fade.h"
class Gameover
{
public:
	Gameover();
	~Gameover();
	void Update();
	void Draw();
	bool Getflag()
	{
		return flag1;
	}
private:
	Font m_font;
	wchar_t mojimoji[256];
	Sprite m_oversprite; //�Q�[���I�[�o�[�̃X�v���C�g
	bool flag = false;
	bool flag1 = false;
};

