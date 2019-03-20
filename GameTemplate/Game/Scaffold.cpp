#include "stdafx.h"
#include "Scaffold.h"
#include "Player.h"
#include "Stage.h"
#include "Game.h"



Scaffold::Scaffold(CVector3 pos, CQuaternion rot, Player* player):
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
	m_model.Init(L"Assets/modelData/karasiba.cmo");
	//m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
	//静的物理オブジェクトを作成
	m_phyStaticObject.CreateMeshObject(m_model, m_position, CQuaternion::Identity());
	//m_charaCon.Init(10.0f, 50.0f, m_position);
}


Scaffold::~Scaffold()
{
}

void Scaffold::FrontMove()
{
	m_position.z -= 5.0f;	
}
void Scaffold::BackMove()
{
	m_position.z += 5.0f;
	

}
void Scaffold::Update()
{

	switch (m_sstate)
	{
	case State_FrontMove:
		FrontMove();
		m_phyStaticObject.Releasehantei();
		Hantei++;
		if (Hantei == 1) {
			m_phyStaticObject.CreateMeshObject(m_model, m_position, m_rotation);
			Hantei = 0;
		}
		if (m_position.z <= -3000.0f) {
			m_sstate = State_BackMove;
		}
		break;
	case State_BackMove:
		BackMove();
		 m_phyStaticObject.Releasehantei();	
		 Hantei++;
		if (Hantei == 1) {
			m_phyStaticObject.CreateMeshObject(m_model, m_position, m_rotation);
			Hantei = 0;
		}
		if (m_position.z >= -1460.0f) {
			m_sstate = State_FrontMove;			
		}
		break;
	}
	m_model.SetShadowReciever(true);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}


void Scaffold::Draw()
{
	
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

