#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{

	//�^�C�g���̃X�v���C�g���������B
	m_sprite.Init(L"Resource/sprite/taittol.dds", 1280, 720);
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
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	if (g_pad[0].IsTrigger(enButtonA) && g_fade->GetState() == Fade::idel) {
	
		//�X�^�[�g�̏����ɂȂ����̂Ńt�F�[�h���J�n����
		g_fade->Fadein();
		m_decisionse.Play(false);
		StratFlag = true;

	}	
	else if (StratFlag==true&&g_fade->GetState() == Fade::idel)
	{

		g_currentScene = new Game;
		m_titlebgm.Stop();
		g_fade->Fadeout();
		delete this;
	}
}
void Title::Draw()
{
	g_graphicsEngine->ChangeBackBaffer();
	m_sprite.Draw();
}