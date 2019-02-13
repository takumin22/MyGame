#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	//MessageBox(nullptr, "Aボタン押してね（´・ω・｀）", "通知", MB_YESNO);
	//2Dを初期化。
	m_sprite.Init(L"Resource/sprite/taittol.dds", 1280, 720);
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}


Title::~Title()
{
}
void Title::Update()
{
	//g_camera2D.Update();
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	if (m_toumei >= 1.0f) {
	  //ゲームシーンを作成する
		g_currentScene = new Game;
		m_sprite.SetclearColor(0.0f);
		m_faderate *= -1;
	}

	
	m_toumei += m_faderate;

	if (g_pad[0].IsTrigger(enButtonA)  && m_toumei == 0.0f) {
		m_faderate = 0.02f;
		m_toumei += m_faderate;
	}	
	if (m_toumei < 0.0f) {

			delete this;
		}
}
void Title::Draw()
{
	m_sprite.Draw();
	//m_fadeSprite.Draw();
}