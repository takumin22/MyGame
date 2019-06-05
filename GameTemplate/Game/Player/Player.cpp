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
#include "Player_StateMachine.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"

//todo 法線マップ。
ID3D11ShaderResourceView* g_normalMapSRV = nullptr;
//todo  ① スペキュラマップ
ID3D11ShaderResourceView* g_specMapSRV = nullptr;
Player::Player() : m_stMa(this)
{

	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Chara_4Hero.cmo");
	m_model.SetAmbientLight(ambientColor);

	m_spjumpse.Init(L"Assets/sound/springjump.wav");

	//tkaファイルの読み込み。
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

	//アニメーションの初期化。
	m_animation.Init(
		m_model,			//アニメーションを流すスキンモデル。
							//これでアニメーションとスキンモデルが関連付けされる。
		m_animationClips,	//アニメーションクリップの配列。
		PlState::EnAnimationClip::enAnimationClip_Num					//アニメーションクリップの数。
	);


	//todo Unityちゃんの法線マップをロード。
	//ファイル名を使って、テクスチャをロードして、ShaderResrouceViewを作成する。
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/Texture_Chara_4Hero_Normal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_normalMapSRV);
	//Unityちゃんのスペキュラマップをロード。
	//ファイル名を使って、テクスチャをロードして、ShaderResourceViewを作成する。
	//DirectX::CreateDDSTextureFromFileEx(
	//	g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/utc_spec.dds", 0,
	//	D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
	//	false, nullptr, &g_specMapSRV);
	//モデルに法線マップを設定する。
	m_model.SetNormalMap(g_normalMapSRV);
	//m_model.SetSpecularMap(g_specMapSRV);
	//サンプルのエフェクトをロードする。
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
	//todo 法線マップを解放。
	if (g_normalMapSRV != nullptr) {
		g_normalMapSRV->Release();
	}
}
void Player::AnimationControl()
{

	//if ( m_charaCon.IsJump() == true) {
	//	m_animation.Play(enAnimationClip_jump,0.2);
	//}
	//else if (m_pstate) {
	//	if ( move.Length() > 0.7f ) {
	//		//走りモーション。
	//		m_animation.Play(enAnimationClip_run, 0.2f);
	//	}
	//	else if (move.Length() > 0.0001f || move.Length() < -0.0001) {
	//		//歩きモーション。
	//		m_animation.Play(enAnimationClip_walk, 0.2f);
	//	}
	//	else if (m_pstate == State_Attack) {
	//		m_animation.Play(enAnimationClip_attack, 0.2f);
	//	}
	//	else if (m_pstate == State_Goal)
	//	{
	//		m_animation.Play(enAnimationClip_salute, 0.2f);
	//	}
	//	else if (m_pstate == State_Damage)
	//	{
	//		m_animation.Play(enAnimationClip_damage, 0.2f);
	//	}
	//	else if (m_pstate == State_Deth)
	//	{
	//		m_animation.Play(enAnimationClip_godown, 0.3);
	//	}
	//	else if( move.Length() == 0.0f){
	//		//待機モーション
	//		m_animation.Play(enAnimationClip_idle, 0.2f);
	//	}
	//}

}
void Player::Attack()
{
	int hoge = -1;
	int num = m_model.GetSkeleton().GetNumBones();
	for (int i = 0; i < num; i++) {
		auto bonename = m_model.GetSkeleton().GetBone(i)->GetName();
		wchar_t moveFilePath[256];
		swprintf_s(moveFilePath, L"Character1_RightHand");
		//腕のボーン番号を名前で取得
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
	//CVector3 toEnemyDlr;
	//float toEnemyLan;
	//for (int i = 0; i <= 4; i++) {
	//	if (m_enemy[i]->GetEnemyDeth() == false) {
	//		////エネミーからプレイヤーに伸びるベクトルを求める。
	//		//CVector3 toEnemyDir = m_position - m_enemy[2]->GetEPosition();
	//		//エネミーからプレイヤーに伸びるベクトルを求める。
	//		 toEnemyDlr = m_position - m_enemy[i]->GetEPosition();
	//		////エネミーまでの距離を求めておく。
	//		//float toEnemyLen = toEnemyDir.Length();
	//		//エネミーまでの距離を求めておく。
	//		toEnemyLan = toEnemyDlr.Length();
	//}
	//		if (toEnemyLan <= 70.0f) {
	//			DamageCount++;
	//			if (DamageCount <= 3) {
	//				m_pstate = State_Damage;
	//			}
	//			else {
	//				m_pstate = State_Deth;
	//			}
	//		}
	//	}
	
}
void Player::SpringJump()
{
	if (g_game->GetNo() <= 1) {
		CVector3 springForward = CVector3::AxisY();
		m_rotation.Multiply(springForward);
		//ジャンプ台からプレイヤーに伸びるベクトルを求める。
		CVector3 toPlayerDir = m_position - m_spring[0]->GetSPosition();
		//ジャンプ台までの距離を求めておく。
		float toPlayerLen = toPlayerDir.Length();
		//正規化
		toPlayerDir.Normalize();
		//springForwardとtoPlayerDirとの内積を計算する。
		float d = springForward.Dot(toPlayerDir);
		//内積の結果をacos関数に渡して、springForwardとtoPlayerDirのなす角を求める。
		float angle = acos(d);

		//ジャンプ台からプレイヤーに伸びるベクトルを求める。
		CVector3 toPlayerDjr = m_position - m_spring[1]->GetSPosition();
		//ジャンプ台までの距離を求めておく。
		float toPlayerLan = toPlayerDjr.Length();
		//正規化
		toPlayerDjr.Normalize();
		//springForwardとtoPlayerDirとの内積を計算する。
		float e = springForward.Dot(toPlayerDjr);
		//内積の結果をacos関数に渡して、springForwardとtoPlayerDirのなす角を求める。
		float ange = acos(e);

		if (fabsf(angle) < CMath::DegToRad(50.0f)
			&& toPlayerLen <= 70.0f ||
			fabsf(ange) < CMath::DegToRad(50.0f)
			&& toPlayerLan <= 70.0f) {
			m_moveSpeed.y += 1300.0f;
		}
	}
		
}
void Player::PlayerPosRetrun()
{
	if (m_position.y <= -500.0f) {
		if (Zanki >= 1) {

			m_position = m_oldposition;
			m_charaCon.SetPosition(m_position);
		}
		m_moveSpeed.y = 0.0f;
		Zanki -= 1;
	}
}
void Player::Scafflod()
{
	if (g_game->GetNo() <= 1) {
		for (int i = 0; i < 2; i++) {
			if (m_scaffold[i]->Getflag() == true) {

				if (m_scaffold[i]->GetState() == m_scaffold[i]->State_FrontMove) {
					m_position.z -= 5.0f;

				}
				else if (m_scaffold[i]->GetState() == m_scaffold[i]->State_BackMove) {
					m_position.z += 5.0f;
				}
			}
		}
	}
	m_charaCon.SetPosition(m_position);

}
void Player::Update()
{
	CVector3 move = CVector3::Zero();
	move.x = g_pad[0].GetLStickXF();
	move.z = g_pad[0].GetLStickYF();
	move.y = 0.0f;
	CQuaternion qRot;
		static float JUMP_SPEED = 700.0f;
		PlayerPosRetrun();
		Scafflod();
		SpringJump();
		//Turn();
		//AnimationControl();
	//switch (m_pstate)
	//{
	//case State_Idel: //待機ステート
	//	m_moveSpeed.x = 0.0f;
	//	m_moveSpeed.z = 0.0f;
	//	Time = 0;
	//	Move();
	//    Scafflod();
	//	if (g_game->GetNo() <= 1) {
	//		Damage();
	//		SpringJump();
	//	}
	//	if (g_pad[0].IsTrigger(enButtonA)) {
	//		m_moveSpeed.y = JUMP_SPEED;
	//		m_pstate = State_Jump;
	//	}
	//	 if (move.Length() >= 0.7f) {
	//		//入力がある。
	//		m_pstate = State_MoveRun;
	//	}
	//	if (g_pad[0].IsTrigger(enButtonB)) {
	//		m_pstate = State_Attack;
	//	}
	//	if (g_game->GetGoal() == true) {
	//		m_pstate = State_Goal;
	//	}
	//	if (m_position.y <= -500.0f) {
	//		//プレイヤーをスタート位置に戻す
	//		m_pstate = State_Return;
	//	}
	//	break;
	//case State_MoveRun:
	//	Move();
	//	Scafflod();
	//	if (g_game->GetNo() <= 1) {
	//		Damage();
	//		SpringJump();
	//	}
	//	
	//	if (move.Length() < 0.7f ) {
	//		//入力がなくなった。
	//		m_pstate = State_Idel;
	//	}
	//	 if (g_pad[0].IsTrigger(enButtonA)) {
	//		//この時点でのXZ方向の速度を記憶しておく。
	//		m_moveSpeedWhenStartJump = m_moveSpeed.Length();
	//		m_moveSpeed.y = JUMP_SPEED;
	//		m_pstate = State_Jump;
	//	}
	//	if (g_pad[0].IsTrigger(enButtonB)) {
	//		m_pstate = State_Attack;
	//	}
	//	if (m_position.y <= -500.0f) {
	//		//プレイヤーをスタート位置に戻す
	//		m_pstate = State_Return;
	//	}
	//	if (g_game->GetGoal() == true) {
	//		m_pstate = State_Goal;
	//	}
	//	break;
	//case State_Jump:
	//	Move();
	//	if (!m_charaCon.IsJump()) {
	//		if (move.Length() < 0.7f) {
	//			//入力がなくなった。
	//			m_pstate = State_Idel;
	//		}
	//		else {
	//			m_pstate = State_MoveRun;
	//		}
	//	}
	//	if (m_position.y <= -500.0f ) {
	//		m_pstate = State_Return;
	//	}
	//	break;
	//case State_Attack:
	//	m_moveSpeed.x = 0.0f;
	//	m_moveSpeed.z = 0.0f;
	//	if (m_animation.IsPlaying() == false) {
	//			m_pstate = State_Idel;
	//		
	//	}
	//	break;
	//case State_SpringJump: //バネジャンプ
	//	m_spjumpse.Play(false);
	//	m_moveSpeed.y += 1300.0f;
	//	m_pstate = State_Idel;
	//	break;
	//case State_Return://スタートに戻る
	//	PlayerPosRetrun();
	//	m_moveSpeed.y = 0.0f;
	//	DamageCount = 0;
	//	m_pstate = State_Idel;
	//	break;
	//case State_Scaffold://足場上
	//    Move();
	//	Scafflod();
	//	for (int i = 0; i < 2; i++) {
	//		if (m_scaffold[i]->GetState() == m_scaffold[i]->State_FrontMove) {
	//			m_position.z -= 2.5f;

	//		}
	//		else if (m_scaffold[i]->GetState() == m_scaffold[i]->State_BackMove) {
	//			m_position.z += 2.5f;
	//		}
	//	}
	//if (g_pad[0].IsTrigger(enButtonA)) {
	//	//この時点でのXZ方向の速度を記憶しておく。
	//	m_moveSpeedWhenStartJump = m_moveSpeed.Length();
	//	m_moveSpeed.y = JUMP_SPEED;
	//	//m_pstate = State_Jump;
	//}
	//if (m_position.y <= -500.0f) {
	//	//プレイヤーをスタート位置に戻す
	//	m_pstate = State_Return;
	//}
 //      m_charaCon.SetPosition(m_position);
	//	break;
	//case State_Damage: //ダメージ(仮)
	//	Time++;
	//	Move();
	//	
	//	 if (Time == 30.0f) {
	//		 m_pstate = State_InvincibleCount;
	//	 }
	//	break;
	//case State_InvincibleCount:  //無敵時間(仮)	
	//	Move();
	//	Time++;
	//	if (g_pad[0].IsTrigger(enButtonA)) {
	//		m_moveSpeed.y = JUMP_SPEED;
	//	}
	//	if (Time== 60.0f) {
	//		m_pstate = State_Idel;
	//	}
	//	break;
	//case State_Deth:  //死亡
	//	m_moveSpeed.x = 0.0f;
	//	m_moveSpeed.z = 0.0f;
	//	Time++;
	//	if (Time >= 60.0f) {
	//		m_pstate = State_Return;
	//	}
	//	break;
	//case State_Goal:
	//	m_moveSpeed.x = 0.0f;
	//	m_moveSpeed.z = 0.0f;

	//	if (g_game->GetGoal() == false) {
	//		m_pstate = State_Idel;
	//	}
	//	break;
	//}

	m_stMa.Update();
	//ワールド行列の更新。
	
	g_shadowMap->RegistShadowCaster(&m_model);
	auto r_pos = m_position;
	CVector3 pos = { 0.0f, -1000.0f, 0.0f,};
	pos *= -1;
	r_pos.x += pos.x;
	r_pos.y += pos.y;
	g_shadowMap->Update(r_pos, m_position);

	//キャラクタを移動させる。
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