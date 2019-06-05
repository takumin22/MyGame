#include "stdafx.h"
#include "Pose.h"


Pose::Pose()
{
	m_posesprite.Init(L"Resource/sprite/Pose.dds", 680, 460);
	m_posesprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_yaji.Init(L"Resource/sprite/yaji.dds", 100, 200);
	m_yaji.Update(m_pos, CQuaternion::Identity(), CVector3::One());
	m_posesprite.SetclearColor(1.0f);
}


Pose::~Pose()
{
}

void Pose::Updata()
{
	m_posesprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_yaji.Update(m_pos, CQuaternion::Identity(), CVector3::One());

	switch (m_pousestate)
	{
	case State_Zokkou:
		if (g_pad[0].IsPress(enButtonDown))
		{
			m_pos.y -= 100.0f;
			m_pos.x -= 80.0f;
			m_pousestate = State_Title;
		}

		break;
	case State_Title:
		if (g_pad[0].IsPress(enButtonUp))
		{
			m_pos.y += 100.0f;
			m_pos.x += 80.0f;
			m_pousestate = State_Zokkou;
		}
		if (g_pad[0].IsPress(enButtonA))
		{
			Flag = true;
		}
		break;
	}
}

void Pose::Draw()
{
	m_posesprite.Draw();
	m_yaji.Draw();
}