#include "stdafx.h"
#include "TurnScaffold.h"
#include "Player.h"


TurnScaffold::TurnScaffold(CVector3 pos, CQuaternion rot, Player* player):
m_position(pos),
m_rotation(rot),
m_player(player)
{
	m_model.Init(L"Assets/modelData/turnasiba.cmo");
	//静的物理オブジェクトを作成
	m_phyStaticObject.CreateMeshObject(m_model, m_position, CQuaternion::Identity());
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}


TurnScaffold::~TurnScaffold()
{
}

void TurnScaffold::Update()
{


	m_phyStaticObject.Releasehantei();
	Hantei = true;
	if (Hantei == true) {
		m_phyStaticObject.CreateMeshObject(m_model, m_position, m_rotation);
		Hantei = false;
	}
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	m_rotation.Multiply(qRot);
	g_shadowMap->RegistShadowCaster(&m_model);
	m_model.SetShadowReciever(true);
	//ワールド行列の更新
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void TurnScaffold::Draw() {
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}