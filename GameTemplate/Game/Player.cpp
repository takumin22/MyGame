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
	m_model.Init(L"Assets/modelData/Chara_4Hero.cmo");
	m_model.SetAmbientLight(ambientColor);

	m_spjumpse.Init(L"Assets/sound/springjump.wav");

	//tka�t�@�C���̓ǂݍ��݁B
	m_animationClips[enAnimationClip_idle].Load(L"Assets/animData/standing.tka");
	m_animationClips[enAnimationClip_idle].SetLoopFlag(true);

	m_animationClips[enAnimationClip_walk].Load(L"Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_walk].SetLoopFlag(true);

	m_animationClips[enAnimationClip_run].Load(L"Assets/animData/run.tka");
	m_animationClips[enAnimationClip_run].SetLoopFlag(true);

	m_animationClips[enAnimationClip_jump].Load(L"Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_jump].SetLoopFlag(false);


	m_animationClips[enAnimationClip_attack].Load(L"Assets/animData/punch.tka");
	m_animationClips[enAnimationClip_attack].SetLoopFlag(false);

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
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Texture_Chara_4Hero_Normal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_normalMapSRV);
	//Unity�����̃X�y�L�����}�b�v�����[�h�B
	//�t�@�C�������g���āA�e�N�X�`�������[�h���āAShaderResourceView���쐬����B
	//DirectX::CreateDDSTextureFromFileEx(
	//	g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/utc_spec.dds", 0,
	//	D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
	//	false, nullptr, &g_specMapSRV);
	//���f���ɖ@���}�b�v��ݒ肷��B
	m_model.SetNormalMap(g_normalMapSRV);
	//m_model.SetSpecularMap(g_specMapSRV);

	//�T���v���̃G�t�F�N�g�����[�h����B
	m_sampleEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/effect/test.efk");
	m_charaCon.Init(15.0f, 42.0f, m_position);
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
}
void Player::Move()
{

		auto MOVE_SPEED = 2500.0f;
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
			cameraForward *= lStick_y * MOVE_SPEED_JUMP * m_deltatime;
			cameraRight *= lStick_x * MOVE_SPEED_JUMP * m_deltatime;
		}
		else {
			cameraForward *= lStick_y * MOVE_SPEED * m_deltatime;
			cameraRight *= lStick_x * MOVE_SPEED * m_deltatime;
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
		m_moveSpeed.x += friction.x * m_deltatime;
		m_moveSpeed.z += friction.z * m_deltatime;
		//�����x��������B
		m_moveSpeed += cameraForward;
		m_moveSpeed += cameraRight;
		m_moveSpeed.y += -1800.0f * m_deltatime;
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
	CVector3 move = CVector3::Zero();
    move.x = g_pad[0].GetLStickXF();
	move.z = g_pad[0].GetLStickYF();
	move.y = 0.0f;
	if ( m_charaCon.IsJump() == true) {
		m_animation.Play(enAnimationClip_jump,0.2);
	}
	else if (m_pstate) {
		if ( move.Length() > 0.7f ) {
			//���胂�[�V�����B
			m_animation.Play(enAnimationClip_run, 0.2f);
		}
		else if (move.Length() > 0.0001f || move.Length() < -0.0001) {
			//�������[�V�����B
			m_animation.Play(enAnimationClip_walk, 0.2f);
		}
		else if (m_pstate == State_Attack) {
			m_animation.Play(enAnimationClip_attack, 0.2f);
		}
		else if (m_pstate == State_Goal)
		{
			m_animation.Play(enAnimationClip_salute, 0.2f);
		}
		else if (m_pstate == State_Damage)
		{
			m_animation.Play(enAnimationClip_damage, 0.2f);
		}
		else if (m_pstate == State_Deth)
		{
			m_animation.Play(enAnimationClip_godown, 0.3);
		}
		else if( move.Length() == 0.0f){
			//�ҋ@���[�V����
			m_animation.Play(enAnimationClip_idle, 0.2f);
		}
	}

}
void Player::Attack()
{
	int hoge = -1;
	int num = m_model.GetSkeleton().GetNumBones();
	for (int i = 0; i < num; i++) {
		auto bonename = m_model.GetSkeleton().GetBone(i)->GetName();
		wchar_t moveFilePath[256];
		swprintf_s(moveFilePath, L"Character1_RightHand");
		//�r�̃{�[���ԍ��𖼑O�Ŏ擾
		int result = wcscmp(moveFilePath, bonename);
		if (result == 0)
		{
			hoge = m_model.GetSkeleton().GetBone(i)->GetNo();
			break;
		}
	}
	armboneNo = hoge;
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
		
	if (fabsf(angle) < CMath::DegToRad(50.0f)
		&& toPlayerLen <= 70.0f ||
		fabsf(ange) < CMath::DegToRad(50.0f)
		&& toPlayerLan <= 70.0f) {
		m_pstate = State_SpringJump;
	}
		
}
void Player::PlayerPosRetrun()
{
	if (Zanki >= 1) {
		if (g_game->GetNo() == 1) {
			m_position.x = 0.0f;
			m_position.y = 15.0f;
			m_position.z = 456.7f;
			m_charaCon.SetPosition(m_position);
		}
		else if (g_game->GetNo() == 2) {
			m_position.x = 0.0f;
			m_position.y = 435.0f;
			m_position.z = 429.0f;
			m_charaCon.SetPosition(m_position);
		}
	}
	Zanki -= 1;
}
void Player::AABB()
{
 //�ȈՓI��AABB
	auto vMax=	m_scaffold[1]->GetScaPosition();
	auto vMin = vMax;
	vMax.x += 200.0f;
	vMax.y += 200.0f;
	vMax.z += 200.0f;
	vMin.x -= 200.0f;
	vMin.y -= 200.0f;
	vMin.z -= 200.0f;
	if (m_position.x <= vMax.x && m_position.x >= vMin.x &&
		m_position.y <= vMax.y && m_position.y >= vMin.y &&
		m_position.z >= vMin.z && m_position.z <= vMax.z  ) {
		syoutotuflag = true;   // �ՓˁI�I
	}
	else {
		syoutotuflag = false; //�Փ˂��Ă��Ȃ�
	}


	auto vMax1 = m_scaffold[0]->GetScaPosition();
	auto vMin1 = vMax1;
	vMax1.x += 200.0f;
	vMax1.y += 200.0f;
	vMax1.z += 200.0f;
	vMin1.x -= 200.0f;
	vMin1.y -= 200.0f;
	vMin1.z -= 200.0f;
	if (m_position.x <= vMax1.x && m_position.x >= vMin1.x &&
		m_position.y <= vMax1.y && m_position.y >= vMin1.y &&
		m_position.z >= vMin1.z && m_position.z <= vMax1.z) {
		syoutotuflag1 = true;   // �ՓˁI�I
	}
	else {
		syoutotuflag1 = false; //�Փ˂��Ă��Ȃ�
	}

	auto vMax2 = m_turnscaffold[0]->GetPosition();
	auto vMin2 = vMax2;
	vMax2.x += 200.0f;
	vMax2.y += 200.0f;
	vMax2.z += 200.0f;
	vMin2.x -= 200.0f;
	vMin2.y -= 200.0f;
	vMin2.z -= 200.0f;
	if (m_position.x <= vMax2.x && m_position.x >= vMin2.x &&
		m_position.y <= vMax2.y && m_position.y >= vMin2.y &&
		m_position.z >= vMin2.z && m_position.z <= vMax2.z) {
		syoutotuflag2 = true;   // �ՓˁI�I
	}
	else {
		syoutotuflag2 = false; //�Փ˂��Ă��Ȃ�
	}
}
void Player::Scafflod()
{
	if (g_game->GetNo() <= 1) {
		AABB();
	}
	if (syoutotuflag == true) {

		m_pstate = State_Scaffold;
	}
	else if (syoutotuflag == false&& syoutotuflag1 == false && m_moveSpeed.LengthSq() < 50.0f * 50.0f) {
		m_pstate = State_Idel;
	}
	//else if (syoutotuflag == false && syoutotuflag1 == false && m_moveSpeed.LengthSq() > 50.0f * 50.0f) {
	//	m_pstate = State_MoveRun;
	//}

    if (syoutotuflag1 == true) {

		m_pstate = State_Scaffold1;

	}

}
void Player::Update()
{
	CVector3 move = CVector3::Zero();
	move.x = g_pad[0].GetLStickXF();
	move.z = g_pad[0].GetLStickYF();
	move.y = 0.0f;
	CQuaternion qRot;
		static float JUMP_SPEED = 700.0f;
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
		if (g_game->GetNo() <= 1) {
			Damage();
			SpringJump();
		}
		if (g_pad[0].IsTrigger(enButtonA)) {
			m_moveSpeed.y = JUMP_SPEED;
			m_pstate = State_Jump;
		}
		 if (move.Length() >= 0.7f) {
			//���͂�����B
			m_pstate = State_MoveRun;
		}
		if (g_pad[0].IsTrigger(enButtonB)) {
			m_pstate = State_Attack;
		}
		if (g_game->GetGoal() == true) {
			m_pstate = State_Goal;
		}
		if (m_position.y <= -500.0f) {
			//�v���C���[���X�^�[�g�ʒu�ɖ߂�
			m_pstate = State_Return;
		}
		if (syoutotuflag2 == true)
		{
			
		}
		break;
	case State_MoveRun:
		Move();
		Scafflod();
		if (g_game->GetNo() <= 1) {
			Damage();
			SpringJump();
		}
		
		if (move.Length() < 0.7f ) {
			//���͂��Ȃ��Ȃ����B
			m_pstate = State_Idel;
		}
		 if (g_pad[0].IsTrigger(enButtonA)) {
			//���̎��_�ł�XZ�����̑��x���L�����Ă����B
			m_moveSpeedWhenStartJump = m_moveSpeed.Length();
			m_moveSpeed.y = JUMP_SPEED;
			m_pstate = State_Jump;
		}
		if (g_pad[0].IsTrigger(enButtonB)) {
			m_pstate = State_Attack;
		}
		if (m_position.y <= -500.0f) {
			//�v���C���[���X�^�[�g�ʒu�ɖ߂�
			m_pstate = State_Return;
		}
		if (g_game->GetGoal() == true) {
			m_pstate = State_Goal;
		}
		if (syoutotuflag2 == true)
		{
			qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
			m_rotation.Multiply(qRot);
		}
		break;
	case State_Jump:
		Move();
		if (!m_charaCon.IsJump()) {
			if (move.Length() < 0.7f) {
				//���͂��Ȃ��Ȃ����B
				m_pstate = State_Idel;
			}
			else {
				m_pstate = State_MoveRun;
			}
		}
		if (m_position.y <= -500.0f ) {
			m_pstate = State_Return;
		}
		break;
	case State_Attack:
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		if (m_animation.IsPlaying() == false) {
				m_pstate = State_Idel;
			
		}

		break;
	case State_SpringJump: //�o�l�W�����v
		m_spjumpse.Play(false);
		m_moveSpeed.y += 1300.0f;
		m_pstate = State_Idel;
		break;
	case State_Return://�X�^�[�g�ɖ߂�
		PlayerPosRetrun();
		m_moveSpeed.y = 0.0f;
		DamageCount = 0;
		m_pstate = State_Idel;
		break;
	case State_Scaffold://�����
	    Move();
		Scafflod();
	if (m_scaffold[1]->GetState() == m_scaffold[1]->State_FrontMove) {
		m_position.z -= 5.0f;

    }
	else if (m_scaffold[1]->GetState() == m_scaffold[1]->State_BackMove) {
		m_position.z += 5.0f;
	}
	if (g_pad[0].IsTrigger(enButtonA)) {
		//���̎��_�ł�XZ�����̑��x���L�����Ă����B
		m_moveSpeedWhenStartJump = m_moveSpeed.Length();
		m_moveSpeed.y = JUMP_SPEED;
		//m_pstate = State_Jump;
	}
       m_charaCon.SetPosition(m_position);
		break;
	case State_Scaffold1:
		Move();
		Scafflod();
		if (m_scaffold[0]->GetState() == m_scaffold[0]->State_FrontMove) {
			
			m_position.z -= 5.0f;
		}
		else if (m_scaffold[0]->GetState() == m_scaffold[0]->State_BackMove) {
				m_position.z += 5.0f;
		}
	 if (g_pad[0].IsTrigger(enButtonA)) {
			//���̎��_�ł�XZ�����̑��x���L�����Ă����B
			m_moveSpeedWhenStartJump = m_moveSpeed.Length();
			m_moveSpeed.y = JUMP_SPEED;
			//m_pstate = State_Jump;
		}
		m_charaCon.SetPosition(m_position);
		break;
	case State_Damage: //�_���[�W(��)
		Time++;
		Move();
		
		 if (Time == 30.0f) {
			 m_pstate = State_InvincibleCount;
		 }
		break;
	case State_InvincibleCount:  //���G����(��)	
		Move();
		Time++;
		if (g_pad[0].IsTrigger(enButtonA)) {
			m_moveSpeed.y = JUMP_SPEED;
		}
		if (Time== 60.0f) {
			m_pstate = State_Idel;
		}
		break;
	case State_Deth:  //���S
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		Time++;
		if (Time >= 60.0f) {
			m_pstate = State_Return;
		}
		break;
	case State_Goal:
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

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
	m_position = m_charaCon.Execute(1.0f / 30.0f, m_moveSpeed);
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