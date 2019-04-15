#include "stdafx.h"
#include "Fade.h"
#include "Sprite.h"

Fade::Fade()
{
	//フェード用のデータを読み込み
	m_texture_fade.Init(L"Resource/sprite/White.dds", 1280.0f, 720.0f);
	m_texture_fade.SetclearColor(0.0f);
}


Fade::~Fade()
{
}
bool Fade::Update()
{
	m_texture_fade.SetclearColor(m_toumei);
	//状態の遷移
	switch (m_fadestate)
	{
	case fadein:
		if (m_toumei >= 1.0f)
		{
			m_toumei = 1.0f;
			return true;
		}
		break;
	case fadeout:
		if (m_toumei <= 0.0f)
		{
			m_toumei = 0.0f;
			return true;
		}
		break;
	case idel:
		return false;
		break;
	default:
		break;
	}
	m_toumei += m_faderate;
	return false;
}
void Fade::Draw()
{
	m_texture_fade.Draw();
}