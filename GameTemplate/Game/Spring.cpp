#include "stdafx.h"
#include "Spring.h"
#include "Player/Player.h"


Spring::Spring(CVector3 pos, CQuaternion rot, Player* player):
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
    //cmoファイルの読み込み
	//静的物理オブジェクトを作成
	m_model.Init(L"Assets/modelData/Spring.cmo");
	m_phyStaticObject.CreateMeshObject(m_model, m_position, CQuaternion::Identity());
    m_model.UpdateWorldMatrix(m_position, m_rotation,m_scale);
}


Spring::~Spring()
{
	m_phyStaticObject.Releasehantei();
	g_shadowMap->UnregistShadowCaster(&m_model);
}
void Spring::Update()
{
	if (m_scale.z <= 1.0f) {
		m_scale.z += 0.2f;
	}
	else if(m_scale.z >= 0.1f) {
		m_scale.z -= 0.2f;
	}
	g_shadowMap->RegistShadowCaster(&m_model);
	m_model.SetShadowReciever(true);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Spring::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}