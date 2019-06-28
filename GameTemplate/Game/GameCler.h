#pragma once
class GameCler
{
public:
	GameCler();
	~GameCler();
	void Update();
	void Darw();
private:
	Sprite m_goalsprite;
	Font m_font;
	wchar_t moji[256];
};

