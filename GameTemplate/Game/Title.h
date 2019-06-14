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

	enum TitleState {
		State_GameState,
		State_StageSelect,
	};
private:
	Sprite m_sprite;			//タイトルのスプライトデータ
	Sprite m_titlelogo;
	Sprite m_yaji;
	CSoundSource m_titlebgm;    //タイトルBGM
	CSoundSource m_decisionse;  //決定音
	CSoundSource m_cursorse;
	bool StratFlag = false;		//スタートフラグ
	TitleState m_titlestate = State_GameState;
	CVector3 m_logopos = { 0.0f,400.0f,0.0f };
	CVector3 m_pos = { -250.0f,-180.0f,0.0f };				//矢印のポジション
	CQuaternion m_rot = CQuaternion::Identity();
};