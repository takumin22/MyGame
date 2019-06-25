#include "stdafx.h"
#include "Gameover.h"


Gameover::Gameover()
{
	m_oversprite.Init(L"Resource/sprite/gameover.dds", 1280, 720);
	m_oversprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}


Gameover::~Gameover()
{
}

void Gameover::Update()
{
	m_oversprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	if (g_pad[0].IsPress(enButtonA) == true && g_fade->GetState() == Fade::idel) {
		g_fade->Fadein();
		flag = true;

	}
	if (flag == true && g_fade->GetState() == Fade::idel)
	{
		g_fade->Fadeout();
		flag = false;
		flag1 = true;
	}
}

void Gameover::Draw()
{
	//g_graphicsEngine->ChangeBackBaffer();
	m_oversprite.Draw();
}