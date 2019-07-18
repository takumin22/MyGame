#include "stdafx.h"
#include "CheckPoint.h"
#include "Player/Player.h"


CheckPoint::CheckPoint()
{
	m_model.Init(L"Assets/modelData/ForestFlag.cmo", enFbxUpAxisZ, { 1.0f,1.0f,2.0f,1.0f });
	m_getse.Init(L"Assets/sound/eyeshine1.wav");
	m_getse.SetVolume(0.8f);
}


CheckPoint::~CheckPoint()
{
}

void CheckPoint::CheckGet()
{
	CVector3 toPlayer = m_position - m_player->GetPosition();
	//ÉvÉåÉCÉÑÅ[Ç‹Ç≈ÇÃãóó£ÇãÅÇﬂÇÈ
	float len = toPlayer.Length();
	if (len <= 20.0f)
	{
		if (seflag == true) {
			m_getse.Play(false);
			seflag = false;
		}
	
		CheckFlag = true;
		m_player->SetPosFlag(false);
	}
}

void CheckPoint::Update()
{
	CheckGet();
	CQuaternion qrot;
	qrot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	m_rotation.Multiply(qrot);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}
void CheckPoint::Draw()
{
	if (CheckFlag == false) {
		m_model.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
}