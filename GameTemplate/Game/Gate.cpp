#include "stdafx.h"
#include "Gate.h"
#include "Coin.h"
#include "Player.h"
#include "Stage.h"

Gate::Gate(CVector3 pos, CQuaternion rot, Player* player, Stage* stage) :
	m_position(pos),
	m_rotation(rot),
	m_player(player),
	m_stage(stage)
{
	m_model.Init(L"Assets/modelData/fence_gate.cmo");
	//静的物理オブジェクトを作成
	m_phyStaticObject.CreateMeshObject(m_model, m_position, CQuaternion::Identity());
}


Gate::~Gate()
{
}

void Gate::Open()
{
	if (m_stage->GetCoinCount() == 0) 
	{

		GateFlag = true;

	}
	if (GateFlag == true)
	{
		if (m_rotation.y <= 0.7f) {
			CQuaternion qRot;
			qRot.SetRotationDeg(CVector3::AxisY(), 5.0f);
			m_rotation.Multiply(qRot);
			m_phyStaticObject.Releasehantei();
		}
		
	}


}


void Gate::Update()
{
	Open();
	m_model.SetShadowReciever(true);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}


void Gate::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}