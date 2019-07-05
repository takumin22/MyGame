#pragma once
#include "Score.h"
#include "Stage.h"
#include "sound/SoundSource.h"
class GameCler
{
public:
	GameCler();
	~GameCler();
	void Relese();
	void ClerFont();
	void Update();
	void FontDraw();
	void Darw();
	enum ScoreDraw {
		 score,
		 timescore,
		 totalscore,
		 end
	};
	void SetPos(CVector3 pos)
	{
		m_spritepos = pos;
	}
	CVector3 GetSpritePos()
	{
		return m_spritepos;
	}
private:
	Sprite m_goalisprite;
	Sprite m_sprite;
	Font m_font;
	CVector3 m_spritepos = { 0.0f,500.0f,0.0f };
	Score m_score;
	Stage* m_stage;
	ScoreDraw m_scorenum = score;
	int ScoreTime = 0;
	wchar_t toubatu[256];
	float m_claerfontscale = 0.7f;
	int m_totalscore = 0;
	float alpha = 0.0;
	bool alphaflag = false;
	CSoundSource m_clerse;
};

