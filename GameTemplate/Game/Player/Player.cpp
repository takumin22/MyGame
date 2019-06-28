#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyFly.h"
#include "Game.h"
#include "Goal.h"
#include "Spring.h"
#include "Scaffold.h"
#include "TurnScaffold.h"
#include "Stage.h"
#include "Coin.h"
#include "HP.h"
#include "RedCoin.h"
#include "Player_StateMachine.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"

//todo �@���}�b�v�B
ID3D11ShaderResourceView* g_normalMapSRV = nullptr;
//todo  �@ �X�y�L�����}�b�v
ID3D11ShaderResourceView* g_specMapSRV = nullptr;
Player::Player() : m_stMa(this)
{

	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/Chara_4Hero.cmo");
	m_model.SetAmbientLight(ambientColor);

	m_spjumpse.Init(L"Assets/sound/springjump.wav");
	m_sprite.Init(L"Resource/sprite/tairyoku.dds", 60, 60);
	m_sprite.Update(m_attackPos, CQuaternion::Identity(), CVector3::One());
	//tka�t�@�C���̓ǂݍ��݁B
	m_animationClips[PlState::EnAnimationClip::enAnimationClip_idle].Load(L"Assets/animData/standing.tka");
	m_animationClips[PlState::EnAnimationClip::enAnimationClip_idle].SetLoopFlag(true);

	m_animationClips[PlState::EnAnimationClip::enAnimationClip_walk].Load(L"Assets/animData/walk.tka");
	m_animationClips[PlState::EnAnimationClip::enAnimationClip_walk].SetLoopFlag(true);

	m_animationClips[PlState::EnAnimationClip::enAnimationClip_run].Load(L"Assets/animData/run.tka");
	m_animationClips[PlState::EnAnimationClip::enAnimationClip_run].SetLoopFlag(true);

	m_animationClips[PlState::EnAnimationClip::enAnimationClip_jump].Load(L"Assets/animData/jump.tka");
	m_animationClips[PlState::EnAnimationClip::enAnimationClip_jump].SetLoopFlag(false);


	m_animationClips[PlState::EnAnimationClip::enAnimationClip_attack].Load(L"Assets/animData/punch.tka");
	m_animationClips[PlState::EnAnimationClip::enAnimationClip_attack].SetLoopFlag(false);

	m_animationClips[PlState::EnAnimationClip::enAnimationClip_damage].Load(L"Assets/animData/damage.tka");
	m_animationClips[PlState::EnAnimationClip::enAnimationClip_damage].SetLoopFlag(false);

	m_animationClips[PlState::EnAnimationClip::enAnimationClip_godown].Load(L"Assets/animData/godown.tka");
	m_animationClips[PlState::EnAnimationClip::enAnimationClip_godown].SetLoopFlag(false);

	m_animationClips[PlState::EnAnimationClip::enAnimationClip_toptojump].Load(L"Assets/animData/toptoground.tka");
	m_animationClips[PlState::EnAnimationClip::enAnimationClip_toptojump].SetLoopFlag(false);

	m_animationClips[PlState::EnAnimationClip::enAnimationClip_salute].Load(L"Assets/animData/salute.tka");
	m_animationClips[PlState::EnAnimationClip::enAnimationClip_salute].SetLoopFlag(false);

	//�A�j���[�V�����̏������B
	m_animation.Init(
		m_model,			//�A�j���[�V�����𗬂��X�L�����f���B
							//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		m_animationClips,	//�A�j���[�V�����N���b�v�̔z��B
		PlState::EnAnimationClip::enAnimationClip_Num					//�A�j���[�V�����N���b�v�̐��B
	);


	//todo Unity�����̖@���}�b�v�����[�h�B
	//�t�@�C�������g���āA�e�N�X�`�������[�h���āAShaderResrouceView���쐬����B
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Texture_Chara_4Hero_Normal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_normalMapSRV);
	//Unity�����̃X�y�L�����}�b�v�����[�h�B
	//�t�@�C�������g���āA�e�N�X�`�������[�h���āAShaderResourceView���쐬����B
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Texture_MetallicSmooth.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_specMapSRV);
	//���f���ɖ@���}�b�v��ݒ肷��B
	m_model.SetNormalMap(g_normalMapSRV);
	//m_model.SetSpecularMap(g_specMapSRV);
	//�T���v���̃G�t�F�N�g�����[�h����B
	m_sampleEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/effect/test.efk");
	m_charaCon.Init(15.0f, 42.0f, m_position);
	m_oldposition = m_position;
	m_stMa.Start();
}


Player::~Player()
{
	m_sampleEffect->Release();
	if (g_graphicsEngine->GetEffekseerManager() != NULL) {
		g_graphicsEngine->GetEffekseerManager()->StopEffect(m_playEffectHandle);
	}
	//todo �@���}�b�v������B
	if (g_normalMapSRV != nullptr) {
		g_normalMapSRV->Release();
	}
	if (g_specMapSRV != nullptr) {
		g_specMapSRV->Release();
	}
	posflag = false;
}
void Player::VecterCler()
{
	m_enemy.clear();
	m_enemyfly.clear();
	m_spring.clear();
	m_redcoin.clear();
	m_turnscaffold.clear();
	posflag = false;
}
void Player::Attack()
{
	
	if (g_pad[0].IsTrigger(enButtonB) == true)
	{
		m_moveSpeed = { 0.0f,0.0f,0.0f };
		m_stMa.Change(PlState::PState::State_Attack);
		m_attackPos.x = m_position.x + m_forward.x * 100.0f;
		m_attackPos.z = m_position.z + m_forward.z * 100.0f;
		m_attackPos.y = m_position.y;
	}
	else {
		m_attackPos = CVector3::Zero();
	}
}
void Player::Damage()
{
	for (int i = 0; i < m_enemy.size(); i++) {
		if (m_enemy[i]->GetEState() != Enemy::EState::State_EDamage) {
			if (m_enemy[i]->GetEnemyDeth() == false) {
				//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
				CVector3 toEnemyDlr = m_position - m_enemy[i]->GetEPosition();
				//�G�l�~�[�܂ł̋��������߂Ă����B
				float toEnemyLan = toEnemyDlr.Length();
				if (toEnemyLan <= 70.0f&& DamageFlag == false || m_position.y <= -500.0f) {
					if (DamageCount <= 2 ) {
						DamageCount++;
						m_stMa.Change(PlState::PState::State_Damage);
						DamageFlag = true;
					}
					else {
						DamageCount++;
						m_stMa.Change(PlState::PState::State_Deth);
					}
				}
			}
		}
	}


	
}
void Player::SpringJump()
{
		CVector3 springForward = CVector3::AxisY();
		m_rotation.Multiply(springForward);
	if (g_game->GetNo() <= 2) {
		for (int i = 0; i < m_spring.size(); i++) {
			//�W�����v�䂩��v���C���[�ɐL�т�x�N�g�������߂�B
			CVector3 toPlayerDir = m_position - m_spring[i]->GetSPosition();
			//�W�����v��܂ł̋��������߂Ă����B
			float toPlayerLen = toPlayerDir.Length();
			//���K��
			toPlayerDir.Normalize();
			//springForward��toPlayerDir�Ƃ̓��ς��v�Z����B
			float d = springForward.Dot(toPlayerDir);
			//���ς̌��ʂ�acos�֐��ɓn���āAspringForward��toPlayerDir�̂Ȃ��p�����߂�B
			float angle = acos(d);
			if (fabsf(angle) < CMath::DegToRad(90.0f)&& toPlayerLen<=90.0
				) {
				m_moveSpeed.y += 1500.0;
			}
		}


	}
		
}
void Player::PlayerPosRetrun()
{

		if (Zanki >= 1) {

			m_position = m_oldposition;
			m_charaCon.SetPosition(m_position);
		}
		m_moveSpeed.y = 0.0f;
		Zanki -= 1;
}
void Player::Scafflod()
{
	if (g_game->GetNo() <= 1) {
		for (int i = 0; i < 2; i++) {
			if (m_scaffold[i]->Getflag() == true) {

				if (m_scaffold[i]->GetState() == m_scaffold[i]->State_FrontMove) {
					m_position.z -= m_scaffold[i]->GetSpeed();

				}
				else if (m_scaffold[i]->GetState() == m_scaffold[i]->State_BackMove) {
					m_position.z += m_scaffold[i]->GetSpeed();
				}
			}
		}
	}
	m_charaCon.SetPosition(m_position);

}
void Player::TurnScafflod()
{
	CVector3 m = CVector3::Zero();
	if (g_game->GetNo() <= 2) {
		for (int i = 0; i < m_turnscaffold.size(); i++) {


			if (m_turnscaffold[i]->Getflag() == true) {
			CVector3 kk = m_position-m_turnscaffold[i]->GetPosition();
			CVector3 kL=kk;
			CQuaternion qrot;
			qrot.SetRotationDeg(CVector3::AxisY(), 2.0f);
			qrot.Multiply(kk);
			m = kk-kL;
			m_position += m;
			}
		}
	}
	m_charaCon.SetPosition(m_position);
}
void Player::Update()
{
	if (m_position.y <= -1500.0f) {
		if (m_animation.IsPlaying() == false)
		{
			if (DamageCount <= 3) {
				m_stMa.Change(PlState::PState::State_Idel);
			}
			else {
				Time++;
				m_moveSpeed = { 0.0f,0.0f,0.0f };
				if (Time >= 60)
				{

					PlayerPosRetrun();
					DamageCount = 0;
					m_stMa.Change(PlState::PState::State_Idel);
				}
			}
		}
	}
	Attack();
	Scafflod();
	SpringJump();
	if (g_game->GetNo() <= 2 ) {
		Damage();
		if (DamageFlag == true)
		{
			Time++;
			if (Time >= 30)
			{
				DamageFlag = false;
				Time = 0;
			}
		}
	}
	m_stMa.Update();
	if (m_animation.IsPlaying() == false)
	{
		if (DamageCount <= 3) {
			m_stMa.Change(PlState::PState::State_Idel);
		}
		else {
			Time++;
			m_moveSpeed = { 0.0f,0.0f,0.0f };
			if (Time >= 60)
			{

				PlayerPosRetrun();
				DamageCount = 0;
				m_stMa.Change(PlState::PState::State_Idel);
			}
		}
	}
	g_shadowMap->RegistShadowCaster(&m_model);
	auto r_pos = m_position;
	CVector3 pos = { 0.0f, -1000.0f, 0.0f, };
	pos *= -1;
	r_pos.x += pos.x;
	r_pos.y += pos.y;
	g_shadowMap->Update(r_pos, m_position);

	//�L�����N�^���ړ�������B
	m_position = m_charaCon.Execute(1.0f / 30.0f, m_moveSpeed);
	TurnScafflod();
	m_mRot.MakeRotationFromQuaternion(m_rotation);
	m_rite = { m_mRot.m[0][0] ,m_mRot.m[0][1],m_mRot.m[0][2] };
	m_up = { m_mRot.m[1][0] ,m_mRot.m[1][1] ,m_mRot.m[1][2] };
	m_forward.x = m_mRot.m[2][0];
	m_forward.y = m_mRot.m[2][1];
	m_forward.z = m_mRot.m[2][2];
	m_forward.Normalize();
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	if (posflag == false)
	{
		m_oldposition = m_position;
		posflag = true;
	}
	m_animation.Update(1.0f / 30.0f);
}
void Player::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}