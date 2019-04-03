#include "stdafx.h"
#include "Coin.h"
#include "Player.h"
#include "Game.h"
#include "graphics/ShadowMap.h"
#include "Gate.h"

Coin::Coin(CVector3 pos, CQuaternion rot,Player* player):
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
	m_model.Init(L"Assets/modelData/Coin.cmo", enFbxUpAxisZ, { 1.0f,1.0f,1.0f});
	m_model.SetAmbientLight(ambientColor);


}


Coin::~Coin()
{
	g_shadowMap->UnregistShadowCaster(&m_model);
}

void Coin::CoinGet() 
{
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toCoin = m_player->GetPosition() - m_position;
	//�v���C���[�܂ł̋��������߂�
	float len = toCoin.Length();
	if (len <= 70.0f) {
	
			CoinGetFlag = true;
			g_game->SetGetCoin(true);
		
	}

}

void Coin::Update()
{


	CoinGet();
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 10.0f);
	m_rotation.Multiply(qRot);
	//���[���h�s��̍X�V
	g_shadowMap->RegistShadowCaster(&m_model);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Coin::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}