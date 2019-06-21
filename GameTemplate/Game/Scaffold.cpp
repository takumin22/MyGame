#include "stdafx.h"
#include "Scaffold.h"
#include "Player/Player.h"
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
}


Scaffold::~Scaffold()
{
}

void Scaffold::AABB()
{
	//簡易的なAABB
	auto vMax = m_position;
	auto vMin = vMax;
	vMax.x += 200.0f;
	vMax.y += 200.0f;
	vMax.z += 200.0f;
	vMin.x -= 200.0f;
	vMin.y -= 200.0f;
	vMin.z -= 200.0f;
	if (m_player->GetPosition().x <= vMax.x && m_player->GetPosition().x >= vMin.x &&
		m_player->GetPosition().y <= vMax.y && m_player->GetPosition().y >= vMin.y &&
		m_player->GetPosition().z >= vMin.z && m_player->GetPosition().z <= vMax.z) {
		syoutotuflag = true;   // 衝突！！
	}
	else {
		syoutotuflag = false; //衝突していない
	}
}
void Scaffold::FrontMove()
{
	m_position.z -= Speed;	
}
void Scaffold::BackMove()
{
	m_position.z += Speed;
}
void Scaffold::Update()
{
	AABB();

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

