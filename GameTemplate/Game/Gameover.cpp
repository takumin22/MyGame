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

	//if (g_fade->GetState() == Fade::idel) 
	//{
	//	//g_fade->Fadeout();
	//}
}

void Gameover::Draw()
{
	//g_graphicsEngine->ChangeBackBaffer();
	m_oversprite.Draw();
}