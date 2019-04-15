#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{

	//2D���������B
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
	
		//�X�^�[�g�̏����ɂȂ����̂Ńt�F�[�h���J�n����
		m_fade.Fadein();
		m_decisionse.Play(false);


	}	


	if (m_fade.Update())
	{
		//�t�F�[�h�̏�ԑJ��
		switch (m_fade.GetState())
		{
		case Fade::fadein:
			//�t�F�[�h�������������Ȃ���ԂɂȂ��Ă���̂�
			//�Q�[���ǂݍ��݂��X�^�[�g������
			g_currentScene = new Game;
			m_titlebgm.Stop();
			m_sprite.SetclearColor(0.0f);
			//�t�F�[�h�𖾂���
			m_fade.Fadeout();
			break;
		case Fade::fadeout:
			//���ׂĂ̏������I�������̂Ń^�C�g����Delete����
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