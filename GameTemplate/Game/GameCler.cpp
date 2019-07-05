#include "stdafx.h"
#include "GameCler.h"
#include "Game.h"


GameCler::GameCler()
{
	m_goalisprite.Init(L"Resource/sprite/GoalSprite.dds", 1280, 720);
	m_goalisprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_sprite.Init(L"Resource/sprite/wood_kanban.dds", 1000, 600);
	m_sprite.Update(m_spritepos, CQuaternion::Identity(), CVector3::One());
	m_clerse.Init(L"Assets/sound/drum-japanese1.wav");
}


GameCler::~GameCler()
{
	
}

void GameCler::Relese()
{
	m_scorenum = score;
}

void GameCler::ClerFont()
{
}

void GameCler::Update()
{


	//m_goalisprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_sprite.Update(m_spritepos, CQuaternion::Identity(), CVector3::One());
	if (m_spritepos.y >= 10.0f)
	{
		m_spritepos.y -= 20.0f;
	}
	m_totalscore = g_game->GetStage()->GetScore() + g_game->GetTimeScore();
}
void GameCler::FontDraw()
{
	int v1 = rand() % 9998 + 1;		// 1 - 99 �͈̔�
	int v2 = rand() % 999;	// 1 - 100 �͈̔�
	int v3 = rand() % 9998 + 1;
	switch (m_scorenum)
	{
	case score:
		swprintf_s(toubatu, L"�X�R�A %04d",v1);
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -200.0f , 100.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_claerfontscale,
			{ 0.0f,1.0f }
		);
		ScoreTime++;
		if (ScoreTime >= 30)
		{
			m_clerse.Play(false);
			m_scorenum = timescore;

		}
		break;
	case timescore:
		swprintf_s(toubatu, L"�X�R�A %04d", g_game->GetStage()->GetScore());
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -200.0f , 100.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_claerfontscale,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"�^�C���X�R�A%03d", v2);
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -300.0f , 30.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_claerfontscale,
			{ 0.0f,1.0f }
		);
		ScoreTime++;
		if (ScoreTime >= 60)
		{
			m_clerse.Play(false);
			m_scorenum = totalscore;
		}
		break;
	case totalscore:
		
		swprintf_s(toubatu, L"�X�R�A %04d", g_game->GetStage()->GetScore());
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -200.0f , 100.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_claerfontscale,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"�^�C���X�R�A%03d", g_game->GetTimeScore());
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -300.0f , 30.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_claerfontscale,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"���v�X�R�A%04d", v3);
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -250.0f , -50.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_claerfontscale,
			{ 0.0f,1.0f }
		);

		ScoreTime++;
		if (ScoreTime >= 90)
		{	
			m_clerse.Play(false);
			m_scorenum = end;
		}
		break;
	case end:
	
		swprintf_s(toubatu, L"�X�R�A %04d", g_game->GetStage()->GetScore());
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -200.0f , 100.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_claerfontscale,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"�^�C���X�R�A%03d", g_game->GetTimeScore());
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -300.0f , 30.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_claerfontscale,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"���v�X�R�A%04d",m_totalscore );
		m_font.Draw(
			toubatu,		//�\�����镶����B
			{ -250.0f , -50.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_claerfontscale,
			{ 0.0f,1.0f }
		);
		m_font.Draw(
			L"A�{�^���Ŏ��̃X�e�[�W��",		//�\�����镶����B
			{ -350.0f , -150.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 0.0f,0.0f,0.0f,alpha },
			0.0f,
			m_claerfontscale,
			{ 0.0f,1.0f }
		);
		ScoreTime = 0;
		if (alphaflag == false)
		{
			alpha += 0.1;
			if (alpha >= 1.0f) {
				alphaflag = true;
			}
		}
		else if(alphaflag == true){
			
			alpha -= 0.1;
			if (alpha <= 0.0f)
			{
				alphaflag = false;
			}
		}
		break;
	}
}

void GameCler::Darw()
{

	m_goalisprite.Draw();
	m_sprite.Draw();
	if (m_spritepos.y <= 10)
	{
		FontDraw();
	}

}