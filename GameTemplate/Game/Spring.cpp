#include "stdafx.h"
#include "Spring.h"
#include "Player.h"


Spring::Spring(CVector3 pos, CQuaternion rot, Player* player):
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
    //cmo�t�@�C���̓ǂݍ���
	//�ÓI�����I�u�W�F�N�g���쐬
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