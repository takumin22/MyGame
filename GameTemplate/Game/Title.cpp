#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{

	//2Dを初期化。
	m_sprite.Init(L"Resource/sprite/taittol.dds", 1280, 720);
	//m_sprite.SetclearColor(0.0f);
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_decisionse.Init(L"Assets/sound/Decision.wav");
	m_decisionse.SetVolume(0.5f);
	m_titlebgm.Init(L"Assets/sound/Title.wav");
	m_titlebgm.SetVolume(0.8f);
	m_titlebgm.Play(true);
}


Title::~Title()
{
}
void Title::Update()
{
	//g_camera2D.Update();
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	if (g_pad[0].IsTrigger(enButtonA)  && m_fade.GetState() == Fade::idel) {
	
		//スタートの条件になったのでフェードを開始する
		m_fade.Fadein();
		m_decisionse.Play(false);


	}	


	if (m_fade.Update())
	{
		//フェードの状態遷移
		switch (m_fade.GetState())
		{
		case Fade::fadein:
			//フェードが完了し見えない状態になっているので
			//ゲーム読み込みをスタートさせる
			g_currentScene = new Game;
			m_titlebgm.Stop();
			m_sprite.SetclearColor(0.0f);
			//フェードを明ける
			m_fade.Fadeout();
			break;
		case Fade::fadeout:
			//すべての処理が終了したのでタイトルをDeleteする
			delete this;
			break;
		default:
			break;
		}
	}

}
void Title::Draw()
{
	g_graphicsEngine->ChangeBackBaffer();
	m_sprite.Draw();
	m_fade.Draw();
}