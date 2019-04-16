#pragma once

#include "IScene.h"
#include "Sprite.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Fade.h"

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
	CSoundSource m_titlebgm;    //タイトルBGM
	CSoundSource m_decisionse;  //決定音
	Font m_font;
	bool StratFlag = false;
};