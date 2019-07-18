#include "stdafx.h"
#include "Gameover.h"
#include "Game.h"


Gameover::Gameover()
{
	m_oversprite.Init(L"Resource/sprite/gameover.dds", 1280, 720);
	m_oversprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_yajisprite.Init(L"Resource/sprite/yaji.dds", 100, 200);
	m_yajisprite.Update(m_yajipos, CQuaternion::Identity(), CVector3::One());
}


Gameover::~Gameover()
{
}

void Gameover::OverClear()
{
	Continueflag = false;
	TitleFlag = false;
}

void Gameover::Update()
{
	m_oversprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_yajisprite.Update(m_yajipos, CQuaternion::Identity(), CVector3::One());
	
	switch (m_overstate)
	{
	case State_Continue:
		if (g_pad[0].IsPress(enButtonA) == true && g_fade->GetState() == Fade::idel) {
			g_fade->Fadein();
			flag = true;
		}
		if (flag == true && g_fade->GetState() == Fade::idel)
		{
			g_fade->Fadeout();
			g_game->GetPlayer()->SetZanki(4);
			flag = false;
			Continueflag = true;
		}
		if (g_pad[0].IsPress(enButtonDown))
		{
			m_yajipos.y -= 150.0f;
			m_yajipos.x -= 160.0f;
			m_overstate = State_Title;
		}
		break;
	case State_Title:
		if (g_pad[0].IsPress(enButtonA) == true && g_fade->GetState() == Fade::idel) {
			g_fade->Fadein();
			flag = true;
		}
		if (flag == true && g_fade->GetState() == Fade::idel)
		{
			g_fade->Fadeout();
			flag = false;
			TitleFlag = true;
		}
		if (g_pad[0].IsPress(enButtonUp))
		{
			m_yajipos.y += 150.0f;
			m_yajipos.x += 160.0f;
			m_overstate = State_Continue;
		}
		break;
	}
}

void Gameover::Draw()
{
	m_oversprite.Draw();
	m_yajisprite.Draw();
}