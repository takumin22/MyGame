#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Goal.h"
#include "Spring.h"
#include "Scaffold.h"
#include "TurnScaffold.h"
#include "Stage.h"
#include "Coin.h"
#include "HP.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"

//todo �@���}�b�v�B
ID3D11ShaderResourceView* g_normalMapSRV = nullptr;
//todo  �@ �X�y�L�����}�b�v
ID3D11ShaderResourceView* g_specMapSRV = nullptr;
Player::Player()
{

	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	m_model.SetAmbientLight(ambientColor);

	//tka�t�@�C���̓ǂݍ��݁B
	m_animationClips[enAnimationClip_idle].Load(L"Assets/animData/standing.tka");
	m_animationClips[enAnimationClip_idle].SetLoopFlag(true);

	m_animationClips[enAnimationClip_walk].Load(L"Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_walk].SetLoopFlag(true);

	m_animationClips[enAnimationClip_run].Load(L"Assets/animData/run.tka");
	m_animationClips[enAnimationClip_run].SetLoopFlag(true);

	m_animationClips[enAnimationClip_jump].Load(L"Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_jump].SetLoopFlag(false);

	m_animationClips[enAnimationClip_damage].Load(L"Assets/animData/damage.tka");
	m_animationClips[enAnimationClip_damage].SetLoopFlag(false);

	m_animationClips[enAnimationClip_godown].Load(L"Assets/animData/godown.tka");
	m_animationClips[enAnimationClip_godown].SetLoopFlag(false);

	m_animationClips[enAnimationClip_toptojump].Load(L"Assets/animData/toptoground.tka");
	m_animationClips[enAnimationClip_toptojump].SetLoopFlag(false);

	m_animationClips[enAnimationClip_salute].Load(L"Assets/animData/salute.tka");
	m_animationClips[enAnimationClip_salute].SetLoopFlag(false);

	//�A�j���[�V�����̏������B
	m_animation.Init(
		m_model,			//�A�j���[�V�����𗬂��X�L�����f���B
							//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		m_animationClips,	//�A�j���[�V�����N���b�v�̔z��B
		enAnimationClip_Num					//�A�j���[�V�����N���b�v�̐��B
	);

	//todo Unity�����̖@���}�b�v�����[�h�B
	//�t�@�C�������g���āA�e�N�X�`�������[�h���āAShaderResrouceView���쐬����B
	//todo Unity�����̖@���}�b�v�����[�h�B
	//�t�@�C�������g���āA�e�N�X�`�������[�h���āAShaderResrouceView���쐬����B
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/utc_nomal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_normalMapSRV);
	//Unity�����̃X�y�L�����}�b�v�����[�h�B
	//�t�@�C�������g���āA�e�N�X�`�������[�h���āAShaderResourceView���쐬����B
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/utc_spec.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_specMapSRV);
	//���f���ɖ@���}�b�v��ݒ肷��B
	m_model.SetNormalMap(g_normalMapSRV);
	m_model.SetSpecularMap(g_specMapSRV);

	
	m_charaCon.Init(10.0f, 45.0f, m_position);
}


Player::~Player()
{
	//todo �@���}�b�v������B
	if (g_normalMapSRV != nullptr) {
		g_normalMapSRV->Release();
	}
}
void Player::Move()
{

		auto MOVE_SPEED = 3500.0f;
		static float MOVE_SPEED_JUMP = 1000.0f;

		//���X�e�B�b�N�̓��͗ʂ��󂯎��B
		auto lStick_x = g_pad[0].GetLStickXF();
		auto lStick_y = g_pad[0].GetLStickYF();
		//�J�����̑O�������ƉE�������擾
		CVector3 cameraForward = g_camera3D.GetForward();
		CVector3 cameraRight = g_camera3D.GetRight();
		//XZ���ʂł̑O�������A�E�����ɕϊ�����B
		cameraForward.y = 0.0f;
		cameraForward.Normalize();
		cameraRight.y = 0.0f;
		cameraRight.Normalize();
		if (m_pstate == State_Jump) {
			//�W�����v���ł��ɂ������]���ł���悤�ɂ���B
			cameraForward *= lStick_y * MOVE_SPEED_JUMP * (1.0f / 60.0f);
			cameraRight *= lStick_x * MOVE_SPEED_JUMP * (1.0f / 60.0f);
		}
		else {
			cameraForward *= lStick_y * MOVE_SPEED * (1.0f / 60.0f);
			cameraRight *= lStick_x * MOVE_SPEED * (1.0f / 60.0f);
		}

		//���C�́B
		auto friction = m_moveSpeed;
		if (m_pstate == State_Jump) {
			//�W�����v���̖��C�́B
			friction *= -2.0f;
		}
		else {
			friction *= -5.0f;
		}
		m_moveSpeed.x += friction.x * (1.0f / 60.0f);
		m_moveSpeed.z += friction.z * (1.0f / 60.0f);
		//�����x��������B
		m_moveSpeed += cameraForward;
		m_moveSpeed += cameraRight;
		m_moveSpeed.y += -1800.0f * (1.0f / 60.0f);
		if (m_pstate == State_Jump) {
			//�ړ����x�ɐ�����������B
			//�W�����v���ɃW�����v�O��葁���Ȃ邱�Ƃ͂Ȃ��B
			auto moveSpeedXZ = CVector3(m_moveSpeed.x, 0.0f, m_moveSpeed.z);

			if (moveSpeedXZ.LengthSq() > m_moveSpeedWhenStartJump * m_moveSpeedWhenStartJump) {
				moveSpeedXZ.Normalize();
				moveSpeedXZ *= m_moveSpeedWhenStartJump;
				m_moveSpeed.x = moveSpeedXZ.x;
				m_moveSpeed.z = moveSpeedXZ.z;

			}
		}
				//m_moveSpeed.y -= 1800.0f * (1.0f / 60.0f);
				//�L�����N�^�[�R���g���[���[�ɂP�t���[���̌o�ߎ���:�b(������)�A���ԃx�[�X�̈ړ����x(������)��n���Ă���B
				//Execute�֐��̒��ōs���Ă���v�Z�͉��L�̂悤�Ȃ��́B
				//
				// CVector3 addPos = m_moveSpeed * ( 1.0f / 60.0f ); //�P�t���[���ňړ�����ʂ��v�Z����B
				// m_position += addPos;  //1�t���[���̈ړ��ʂ����W�ɉ��Z����B������I�C���[�ϕ��Ƃ����B
				//m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
				
			
		}
void Player::Turn()
{
	auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	if (moveSpeedXZ.LengthSq() < 1.0f) {
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotation(CVector3::AxisY(), angle);
}
void Player::AnimationControl()
{
	CVector3 stick;

	if (m_pstate == State_Jump) {
		m_animation.Play(enAnimationClip_jump, 0.1f);
	}
	else if (m_pstate == State_MoveRun
		|| m_pstate == State_Idel
		) {
		if (m_moveSpeed.Length() > 300.0f /** 300.0f*/) {
			//���胂�[�V�����B
			m_animation.Play(enAnimationClip_run, 0.2f);
		}
		else if (m_moveSpeed.Length() > 30.0f /** 30.0f*/) {
			//���胂�[�V�����B
			m_animation.Play(enAnimationClip_walk, 0.2f);
		}
		else {
			//�ҋ@���[�V����
			m_animation.Play(enAnimationClip_idle, 0.2f);
		}
	}

}
void Player::Damage()
{
	if (m_enemy[0]->GetEnemyDeth() == false) {
		////�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
		//CVector3 toEnemyDir = m_position - m_enemy[2]->GetEPosition();
		//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
		CVector3 toEnemyDlr = m_position - m_enemy[0]->GetEPosition();
		////�G�l�~�[�܂ł̋��������߂Ă����B
		//float toEnemyLen = toEnemyDir.Length();
		//�G�l�~�[�܂ł̋��������߂Ă����B
		float toEnemyLan = toEnemyDlr.Length();
		if (toEnemyLan <= 70.0f) {
			DamageCount++;

			if (DamageCount <= 3) {
				m_pstate = State_Damage;
			}
			else {
				m_pstate = State_Deth;
			}
		}
	}
}
void Player::SpringJump()
{

		m_animation.Play(enAnimationClip_jump, 0.2f);
		m_moveSpeed.y += 1300.0f;
		m_pstate = State_Idel;
		
		
}
void Player::PlayerPosRetrun()
{
	if (g_game->GetNo() == 1) {
		m_position.x = 0.0f;
		m_position.y = 15.0f;
		m_position.z = 456.7f;
		m_charaCon.SetPosition(m_position);
	}
	else if (g_game->GetNo() == 2) {
		m_position.x = -315.0f;
		m_position.y = 2.5f;
		m_position.z = 214.0f;
		m_charaCon.SetPosition(m_position);
	}
}
void Player::AABB()
{
 
	auto vMax=	m_scaffold[1]->GetScaPosition();
	auto vMin = vMax;
	vMax.x += 100.0f;
	vMax.y += 50.0f;
	vMax.z += 100.0f;
	vMin.x -= 100.0f;
	vMin.y -= 50.0f;
	vMin.z -= 100.0f;
	if (m_position.x <= vMax.x && m_position.x >= vMin.x &&
		m_position.y <= vMax.y && m_position.y >= vMin.y &&
		m_position.z >= vMin.z && m_position.z <= vMax.z  ) {
		kariflag = true;   // �ՓˁI�I
	}
	else {
		kariflag = false; //�Փ˂��Ă��Ȃ�
	}


	auto vMax1 = m_scaffold[0]->GetScaPosition();
	auto vMin1 = vMax1;
	vMax1.x += 100.0f;
	vMax1.y += 50.0f;
	vMax1.z += 100.0f;
	vMin1.x -= 100.0f;
	vMin1.y -= 50.0f;
	vMin1.z -= 100.0f;
	if (m_position.x <= vMax1.x && m_position.x >= vMin1.x &&
		m_position.y <= vMax1.y && m_position.y >= vMin1.y &&
		m_position.z >= vMin1.z && m_position.z <= vMax1.z) {
		kariflag1 = true;   // �ՓˁI�I
	}
	else {
		kariflag1 = false; //�Փ˂��Ă��Ȃ�
	}
}
void Player::Scafflod()
{

	AABB();
	if (kariflag == true) {

		m_pstate = State_Scaffold;
	}
	else if (kariflag == false&&kariflag1 == false && m_moveSpeed.LengthSq() < 50.0f * 50.0f) {
		m_pstate = State_Idel;
	}
	else if (kariflag == false && kariflag1 == false && m_moveSpeed.LengthSq() > 0.001f) {
		m_pstate = State_MoveRun;
	}

    if (kariflag1 == true) {

		m_pstate = State_Scaffold1;

	}

}
void Player::Update()
{



		CVector3 springForward = CVector3::AxisY();
		m_rotation.Multiply(springForward);
		//�W�����v�䂩��v���C���[�ɐL�т�x�N�g�������߂�B
		CVector3 toPlayerDir = m_position - m_spring[0]->GetSPosition();
		//�W�����v��܂ł̋��������߂Ă����B
		float toPlayerLen = toPlayerDir.Length();
		//���K��
		toPlayerDir.Normalize();
		//springForward��toPlayerDir�Ƃ̓��ς��v�Z����B
		float d = springForward.Dot(toPlayerDir);
		//���ς̌��ʂ�acos�֐��ɓn���āAspringForward��toPlayerDir�̂Ȃ��p�����߂�B
		float angle = acos(d);

		//�W�����v�䂩��v���C���[�ɐL�т�x�N�g�������߂�B
		CVector3 toPlayerDjr = m_position - m_spring[1]->GetSPosition();
		//�W�����v��܂ł̋��������߂Ă����B
		float toPlayerLan = toPlayerDjr.Length();
		//���K��
		toPlayerDjr.Normalize();
		//springForward��toPlayerDir�Ƃ̓��ς��v�Z����B
		float e = springForward.Dot(toPlayerDjr);
		//���ς̌��ʂ�acos�֐��ɓn���āAspringForward��toPlayerDir�̂Ȃ��p�����߂�B
		float ange = acos(e);
		static float JUMP_SPEED = 500.0f;
		Turn();
		AnimationControl();
	switch (m_pstate)
	{
	case State_Idel: //�ҋ@�X�e�[�g
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		Time = 0;
		Move();
	    Scafflod();
		Damage();
		if (g_pad[0].IsTrigger(enButtonA)) {
			m_moveSpeed.y = JUMP_SPEED;
			m_pstate = State_Jump;
		}
		else if (m_moveSpeed.LengthSq() > 0.001f) {
			//���͂�����B
			m_pstate = State_MoveRun;
		}
		if (g_game->GetGoal() == true) {
			m_pstate = State_Goal;
		}
		if (fabsf(angle) < CMath::DegToRad(50.0f)
			&&toPlayerLen <= 70.0f ||
			fabsf(ange) < CMath::DegToRad(50.0f)
			&& toPlayerLan <= 70.0f) {
			m_pstate = State_SpringJump;
		}
		if (m_position.y <= -500.0f) {
			m_pstate = State_Return;
		}
		break;
	case State_MoveRun:
		Move();
		Scafflod();
		Damage();
		if (m_moveSpeed.LengthSq() < 30.0f * 30.0f) {
			//���͂��Ȃ��Ȃ����B
			m_pstate = State_Idel;
		}
		else if (g_pad[0].IsTrigger(enButtonA)) {
			//���̎��_�ł�XZ�����̑��x���L�����Ă����B
			m_moveSpeedWhenStartJump = m_moveSpeed.Length();
			m_moveSpeed.y = JUMP_SPEED;
			m_pstate = State_Jump;
		}
		if (m_position.y <= -500.0f) {
			m_pstate = State_Return;
		}
		if (fabsf(angle) < CMath::DegToRad(50.0f)
			&& toPlayerLen <= 70.0f ||
			fabsf(ange) < CMath::DegToRad(50.0f)
			&& toPlayerLan <= 70.0f) {
			m_pstate = State_SpringJump;
		}
		if (g_game->GetGoal() == true) {
			m_pstate = State_Goal;
		}
		break;
	case State_Jump:
		Move();
		if (!m_charaCon.IsJump()) {
			if (m_moveSpeed.LengthSq() < 50.0f * 50.0f) {
				//���͂��Ȃ��Ȃ����B
				m_pstate = State_Idel;
			}
			else {
				m_pstate = State_MoveRun;
			}
		}
		if (m_position.y <= -500.0f) {
			m_pstate = State_Return;
		}
		break;
	case State_SpringJump: //�o�l�W�����v
        SpringJump();
		break;
	case State_Return://�X�^�[�g�ɖ߂�
		PlayerPosRetrun();
		DamageCount = 0;
		m_pstate = State_Idel;
		break;
	case State_Scaffold://�����
	    Move();
		Scafflod();
	if (m_scaffold[1]->m_sstate == m_scaffold[1]->State_FrontMove) {
		m_position.z -= 5.0f;

    }
	else if (m_scaffold[1]->m_sstate == m_scaffold[1]->State_BackMove) {
		m_position.z += 5.0f;
	}
	if (g_pad[0].IsTrigger(enButtonA)) {
		//���̎��_�ł�XZ�����̑��x���L�����Ă����B
		m_moveSpeedWhenStartJump = m_moveSpeed.Length();
		m_moveSpeed.y = JUMP_SPEED;
		m_pstate = State_Jump;
	}
       m_charaCon.SetPosition(m_position);
		break;
	case State_Scaffold1:
		Move();
		Scafflod();
		if (m_scaffold[0]->m_sstate == m_scaffold[0]->State_FrontMove) {
			m_position.z -= 5.0f;


		}
		else if (m_scaffold[0]->m_sstate == m_scaffold[0]->State_BackMove) {
				m_position.z += 5.0f;
		}
	 if (g_pad[0].IsTrigger(enButtonA)) {
			//���̎��_�ł�XZ�����̑��x���L�����Ă����B
			m_moveSpeedWhenStartJump = m_moveSpeed.Length();
			m_moveSpeed.y = JUMP_SPEED;
			m_pstate = State_Jump;
		}
		m_charaCon.SetPosition(m_position);
		break;
	case State_Damage: //�_���[�W(��)
		Time++;
		Move();
		 m_animation.Play(enAnimationClip_damage, 0.01f);
		 if (Time == 30.0f) {
			 m_pstate = State_InvincibleCount;
		 }
		break;
	case State_InvincibleCount:  //���G����(��)	
		Move();
		Time++;
		if (Time== 60.0f) {
			m_pstate = State_Idel;
		}
		break;
	case State_Deth:  //���S
		m_animation.Play(5, 0.3);
		Time++;
		if (Time >= 60.0f) {
			m_pstate = State_Return;
		}
		break;
	case State_Goal:
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		m_animation.Play(enAnimationClip_salute, 0.2f);
		if (g_game->GetGoal() == false) {
			m_pstate = State_Idel;
		}
		break;
	}

	//���[���h�s��̍X�V�B
	
	g_shadowMap->RegistShadowCaster(&m_model);
	auto r_pos = m_position;
	CVector3 pos = { 0.0f, -1000.0f, 0.0f,};
	pos *= -1;
	r_pos.x += pos.x;
	r_pos.y += pos.y;
	g_shadowMap->Update(r_pos, m_position);

	//�L�����N�^���ړ�������B
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
	m_mRot.MakeRotationFromQuaternion(m_rotation);
	m_rite = { m_mRot.m[0][0] ,m_mRot.m[0][1],m_mRot.m[0][2] };
	m_up = { m_mRot.m[1][0] ,m_mRot.m[1][1] ,m_mRot.m[1][2] };
	m_forward = { m_mRot.m[2][0] ,m_mRot.m[2][1] ,m_mRot.m[2][2] };
	m_model.UpdateWorldMatrix(m_position, m_rotation,m_scale);
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