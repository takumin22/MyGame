#include "stdafx.h"
#include "Spring.h"
#include "Player.h"


Spring::Spring(CVector3 pos, CQuaternion rot, Player* player):
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
    //cmo�t�@�C���̓ǂݍ���
	m_model.Init(L"Assets/modelData/Spring.cmo");

	/*m_animationClips[enAnimationClip_spring].Load(L"Assets/animData/spring.tka");
	m_animationClips[enAnimationClip_spring].SetLoopFlag(true);*/

	//�A�j���[�V�����̏������B
	//m_animation.Init(
	//	m_model,			//�A�j���[�V�����𗬂��X�L�����f���B
	//						//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
	//	m_animationClips,	//�A�j���[�V�����N���b�v�̔z��B
	//	enAnimationClip_Num					//�A�j���[�V�����N���b�v�̐��B
	//);
	//�ÓI�����I�u�W�F�N�g���쐬
	m_phyStaticObject.CreateMeshObject(m_model, m_position, CQuaternion::Identity());
    m_model.UpdateWorldMatrix(m_position, m_rotation,m_scale);
}


Spring::~Spring()
{
	m_phyStaticObject.Releasehantei();
	g_shadowMap->UnregistShadowCaster(&m_model);
}
void Spring::SpringJump()
{
	//CVector3 springForward = CVector3::AxisY();
	//m_rotation.Multiply(springForward);
	////�W�����v�䂩��v���C���[�ɐL�т�x�N�g�������߂�B
	//CVector3 toPlayerDir = m_player->GetPosition() - m_position;
	////�W�����v��܂ł̋��������߂Ă����B
	//float toPlayerLen = toPlayerDir.Length();
	////���K��
	//toPlayerDir.Normalize();
	////springForward��toPlayerDir�Ƃ̓��ς��v�Z����B
	//float d = springForward.Dot(toPlayerDir);
	////���ς̌��ʂ�acos�֐��ɓn���āAspringForward��toPlayerDir�̂Ȃ��p�����߂�B
	//float angle = acos(d);

}
void Spring::SpringAnimation()
{
	CVector3 springForward = CVector3::AxisY();
	//spring����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toPlayerDir = m_position - m_player->GetPosition();
	//spring�܂ł̋��������߂Ă����B
	float toPlayerLen = toPlayerDir.Length();
	//���K��
	toPlayerDir.Normalize();
	//springForward��toPlayerDir�Ƃ̓��ς��v�Z����B
	float d = springForward.Dot(toPlayerDir);
	//���ς̌��ʂ�acos�֐��ɓn���āAspringForward��toPlayerDir�̂Ȃ��p�����߂�B
	float angle = acos(d);
	if (toPlayerLen <= 70.0f) {
		//m_player->SetMoveSpeed(1300.0f);
	}
	
}
void Spring::Update()
{
	//SpringAnimation();
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