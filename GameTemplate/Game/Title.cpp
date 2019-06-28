#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "StageSelect.h"

Title::Title()
{

	//タイトルのスプライトを初期化。
	m_sprite.Init(L"Resource/sprite/taittol1.dds", 1280, 720);
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_decisionse.Init(L"Assets/sound/Decision.wav");
	m_decisionse.SetVolume(0.5f);
	m_cursorse.Init(L"Assets/sound/cursor7.wav");
	m_yaji.Init(L"Resource/sprite/yaji.dds", 100, 200);
	m_yaji.Update(m_pos, m_rot ,CVector3::One());
	m_titlelogo.Init(L"Resource/sprite/Title logo.dds", 1280, 720);
	m_titlelogo.Update(m_logopos, CQuaternion::Identity(), CVector3::One());
	m_titlebgm.Init(L"Assets/sound/Title.wav");
	m_titlebgm.SetVolume(0.8f);

}


Title::~Title()
{
	
}
void Title::Update()

{	
	m_titlebgm.Play(true);
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_yaji.Update(m_pos,m_rot, CVector3::One());
	m_titlelogo.Update(m_logopos, CQuaternion::Identity(), CVector3::One());
	if (m_logopos.y >= 200.0f) {
		m_logopos.y -= 2.0f;
	}

	switch (m_titlestate)
	{
	case State_GameState:
		if (g_pad[0].IsPress(enButtonDown))
		{
			m_pos.y -= 130.0f;
			m_pos.x -= 80.0f;
			m_cursorse.Play(false);
			//g_currentScene->SetSceneNo(1);
			m_titlestate = State_StageSelect;
		}
		if (g_pad[0].IsTrigger(enButtonA) && g_fade->GetState() == Fade::idel) {

			//スタートの条件になったのでフェードを開始する
			g_fade->Fadein();
			m_decisionse.Play(false);
			StratFlag = true;

		}
		else if (StratFlag == true && g_fade->GetState() == Fade::idel)
		{

			g_currentScene = new Game;
			//m_titlebgm.Stop();
			g_fade->Fadeout();
			delete this;
		}
		break;
	case State_StageSelect:
		if (g_pad[0].IsPress(enButtonUp))
		{
			m_pos.y += 130.0f;
			m_pos.x += 80.0f;
			m_cursorse.Play(false);
			m_titlestate = State_GameState;
		}
		if (g_pad[0].IsTrigger(enButtonA) && g_fade->GetState() == Fade::idel) {

			//スタートの条件になったのでフェードを開始する
			g_fade->Fadein();
			m_decisionse.Play(false);
			StratFlag = true;

		}
		else if (StratFlag == true && g_fade->GetState() == Fade::idel)
		{

			g_currentScene = new StageSelect;
			m_titlebgm.Stop();
			g_fade->Fadeout();
			delete this;
		}
		break;
	}
}
void Title::Draw()
{
	g_graphicsEngine->ChangeBackBaffer();
	m_sprite.Draw();
	m_yaji.Draw();
	m_titlelogo.Draw();
}