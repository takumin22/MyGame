#pragma once

#include "IScene.h"
#include "Sprite.h"
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
};