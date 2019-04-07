#pragma once

#include "IScene.h"
#include "Sprite.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Title : public IScene
{
public:
	Title();
	~Title();
	//オーバーライドした関数にはoverride修飾子をつけていると幸せになれる。
	void Update() override;
	//オーバーライドした関数にはoverride修飾子をつけていると幸せになれる。
	

	//タイプミスをしたときにコンパイルエラーになって教えてくれる。
	void Draw() override;
private:
	Sprite m_sprite;
	float m_toumei = 0.0f;									//フェイドの度合い
	float m_faderate = 0.0f;
	CSoundSource m_titlebgm;
	CSoundSource m_decisionse;  //決定音
	Font m_font;
};