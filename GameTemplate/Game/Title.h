#pragma once

#include "IScene.h"
#include "Sprite.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Fade.h"

class Title : public IScene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Title();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Title();
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
private:
	Sprite m_sprite;			//タイトルのスプライトデータ
	CSoundSource m_titlebgm;    //タイトルBGM
	CSoundSource m_decisionse;  //決定音
	bool StratFlag = false;		//スタートフラグ
};