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
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);


	//tkaファイルの読み込み。
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

	//アニメーションの初期化。
	m_animation.Init(
		m_model,			//アニメーションを流すスキンモデル。
							//これでアニメーションとスキンモデルが関連付けされる。
		m_animationClips,	//アニメーションクリップの配列。
		enAnimationClip_Num					//アニメーションクリップの数。
	);
	
	m_charaCon.Init(10.0f, 45.0f, m_position);
}


Player::~Player()
{
}
void Player::Move()
{

	if (g_pad[0].IsPress(enButtonB) == false) {

		if (g_pad[0].IsTrigger(enButtonA) == true
			&& m_charaCon.IsOnGround() == true
			) {
			m_moveSpeed.y += 490.0f;
		}
		//左スティックの入力量を受け取る。
		auto lStick_x = g_pad[0].GetLStickXF();
		auto lStick_y = g_pad[0].GetLStickYF();
		//カメラの前方方向と右方向を取得
		CVector3 cameraForward = g_camera3D.GetForward();
		CVector3 cameraRight = g_camera3D.GetRight();
		//XZ平面での前方方向、右方向に変換する。
		cameraForward.y = 0.0f;
		cameraForward.Normalize();
		cameraRight.y = 0.0f;
		cameraRight.Normalize();
		        ////XZ成分の移動速度をクリア。
		    m_moveSpeed.x *= 0.7f;
			m_moveSpeed.z *= 0.7f;
		m_moveSpeed += cameraForward * lStick_y * 450.0f;	//奥方向への移動速度を代入。
		m_moveSpeed += cameraRight * lStick_x * 450.0f;		//右方向への移動速度を加算。
			m_moveSpeed.z = min(450.0f,m_moveSpeed.z);
			m_moveSpeed.z = max(-450.0f, m_moveSpeed.z);
			m_moveSpeed.x = min(450.0f, m_moveSpeed.x);
			m_moveSpeed.x = max(-450.0f, m_moveSpeed.x);
		//Y方向の移動速度は重力加速を行う。
		//加速度を加える。
		//m_moveSpeed += cameraForward;
		//m_moveSpeed += cameraRight;
		m_moveSpeed.y -= 1800.0f * (1.0f / 60.0f);
		//キャラクターコントローラーに１フレームの経過時間:秒(第一引数)、時間ベースの移動速度(第二引数)を渡している。
		//Execute関数の中で行っている計算は下記のようなもの。
		//
		// CVector3 addPos = m_moveSpeed * ( 1.0f / 60.0f ); //１フレームで移動する量を計算する。
		// m_position += addPos;  //1フレームの移動量を座標に加算する。これをオイラー積分という。
		m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
	}
}
void Player::MoveRun()
{
	if (g_pad[0].IsPress(enButtonB) == true) {
		if (g_pad[0].IsTrigger(enButtonA) == true
			&& m_charaCon.IsOnGround() == true
			) {
			m_moveSpeed.y += 490.0f;
		}
		//左スティックの入力量を受け取る。
		float lStick_x = g_pad[0].GetLStickXF();
		float lStick_y = g_pad[0].GetLStickYF();
		//カメラの前方方向と右方向を取得
		auto cameraForward = g_camera3D.GetForward();
		auto cameraRight = g_camera3D.GetRight();
		//XZ平面での前方方向、右方向に変換する。
		cameraForward.y = 0.0f;
		cameraForward.Normalize();
		cameraRight.y = 0.0f;
		cameraRight.Normalize();
		////XZ成分の移動速度をクリア。
		m_moveSpeed.x = 0.8f;
		m_moveSpeed.z = 0.8f;
		
		m_moveSpeed += cameraForward *lStick_y * 650.0f;	//奥方向への移動速度を代入。
		m_moveSpeed += cameraRight *lStick_x * 650.0f;		//右方向への移動速度を加算。
		//m_moveSpeed.z = min(450.0f, m_moveSpeed.z);
		//m_moveSpeed.z = max(-450.0f, m_moveSpeed.z);
		//m_moveSpeed.x = min(450.0f, m_moveSpeed.x);
		//m_moveSpeed.x = max(-450.0f, m_moveSpeed.x);

															
		m_moveSpeed.y -= 1800.0f * (1.0f / 60.0f);//Y方向の移動速度は重力加速を行う。

		//キャラクターコントローラーに１フレームの経過時間:秒(第一引数)、時間ベースの移動速度(第二引数)を渡している。
		//Execute関数の中で行っている計算は下記のようなもの。
		//
		// CVector3 addPos = moveSpeed * ( 1.0f / 60.0f ); //１フレームで移動する量を計算する。
		// position += addPos;  //1フレームの移動量を座標に加算する。これをオイラー積分という。
		m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
	}
}
void Player::Turn()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rotation.SetRotation(CVector3::AxisY(), angle);
}
void Player::AnimationControl()
{
	CVector3 stick;

	if (!m_charaCon.IsJump()) {
		if (stick.x = g_pad[0].GetLStickXF()&& g_pad[0].IsPress(enButtonB) == false) {
			m_animation.Play(enAnimationClip_walk,0.2f);
		}
		else if (stick.y = g_pad[0].GetLStickYF()&& g_pad[0].IsPress(enButtonB) == false) {
			m_animation.Play(enAnimationClip_walk,0.2f);
		}
		else if (stick.x = g_pad[0].GetLStickXF() && g_pad[0].IsPress(enButtonB) == true) {
			m_animation.Play(enAnimationClip_run, 0.2f);
		}
		else if (stick.y = g_pad[0].GetLStickYF() && g_pad[0].IsPress(enButtonB) == true) {
			m_animation.Play(enAnimationClip_run, 0.2f);
		}
		//else if (g_game->GetGoal() == true) {

		//	m_pstate = State_Goal;
		//}
		else {
			m_animation.Play(enAnimationClip_idle,0.2f);
		}

	}
	else {
		if (m_charaCon.IsOnGround()== false&&g_pad[0].IsTrigger(enButtonA) == true) {
			m_animation.Play(enAnimationClip_jump, 0.1f);
		}
	}
}
void Player::Damage()
{
	if (m_enemy[0]->GetEnemyDeth() == false) {
		////エネミーからプレイヤーに伸びるベクトルを求める。
		//CVector3 toEnemyDir = m_position - m_enemy[2]->GetEPosition();
		//エネミーからプレイヤーに伸びるベクトルを求める。
		CVector3 toEnemyDlr = m_position - m_enemy[0]->GetEPosition();
		////エネミーまでの距離を求めておく。
		//float toEnemyLen = toEnemyDir.Length();
		//エネミーまでの距離を求めておく。
		float toEnemyLan = toEnemyDlr.Length();
		if (toEnemyLan <= 70.0f) {
			DamageCount += 1;
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
		m_moveSpeed.y += 650.0f;
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
		kariflag = true;   // 衝突！！
	}
	else {
		kariflag = false; //衝突していない
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
		kariflag1 = true;   // 衝突！！
	}
	else {
		kariflag1 = false; //衝突していない
	}
}
void Player::Scafflod()
{

	AABB();
	if (kariflag == true) {

		m_pstate = State_Scaffold;
	}
	else if (kariflag == false&&kariflag1 == false) {
		m_pstate = State_Idel;
	}

    if (kariflag1 == true) {

		m_pstate = State_Scaffold1;
	}

}
void Player::Distans() {
}
void Player::Update()
{



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
	
	switch (m_pstate)
	{
	case State_Idel: //待機ステート
		//m_moveSpeed.x = 0.0f;
		//m_moveSpeed.z = 0.0f;
		Time = 0;
		Move();
		MoveRun();
		Turn();
		AnimationControl();
	    Scafflod();
		Damage();

		if (g_game->GetGoal() == true) {
			m_pstate = State_Goal;
		}
		//if (fabsf(angle) < CMath::DegToRad(50.0f)
		//	&&toPlayerLen <= 70.0f) {
		//	m_pstate = State_SpringJump;
		//}
		if (m_position.y <= -500.0f) {
			m_pstate = State_Return;
		}
		break;
	case State_MoveRun:
		break;
	case State_SpringJump: //バネジャンプ
        SpringJump();
		break;
	case State_Return://スタートに戻る
		PlayerPosRetrun();
		DamageCount = 0;
		m_pstate = State_Idel;
		break;
	case State_Scaffold://足場上
	    Move();
		MoveRun();
	    Turn();
		AnimationControl();
		Scafflod();
	if (m_scaffold[1]->m_sstate == m_scaffold[1]->State_FrontMove) {
		m_position.z += 5.0f;

    }
	else if (m_scaffold[1]->m_sstate == m_scaffold[1]->State_BackMove) {
		m_position.z -= 5.0f;
	}
        m_charaCon.SetPosition(m_position);
		break;
	case State_Scaffold1:
		Move();
		MoveRun();
		Turn();
		AnimationControl();
		Scafflod();
		if (m_scaffold[0]->m_sstate == m_scaffold[0]->State_FrontMove) {
			m_position.z += 5.0f;

		}
		else if (m_scaffold[0]->m_sstate == m_scaffold[0]->State_BackMove) {
			m_position.z -= 5.0f;
		}
		m_charaCon.SetPosition(m_position);
		break;
	case State_Damage: //ダメージ(仮)
		Time++;
		 m_animation.Play(enAnimationClip_damage, 0.01f);
		 if (Time == 30.0f) {
			 m_pstate = State_InvincibleCount;
		 }
		break;
	case State_InvincibleCount:  //無敵時間(仮)	
		Move();
		MoveRun();
		Turn();
		AnimationControl();
		Time++;
		if (Time== 60.0f) {
			m_pstate = State_Idel;
		}
		break;
	case State_Deth:  //死亡
		m_animation.Play(5, 0.3);
		Time++;
		if (Time >= 60.0f) {
			m_pstate = State_Return;
		}
		break;
	case State_Goal:
		m_animation.Play(enAnimationClip_salute, 0.2f);
		if (g_game->GetGoal() == false) {
			m_pstate = State_Idel;
		}
		break;
	}

	//ワールド行列の更新。
	
	g_shadowMap->RegistShadowCaster(&m_model);
	auto r_pos = m_position;
	CVector3 pos = { 0.0f, -1000.0f, 0.0f,};
	pos *= -1;
	r_pos.x += pos.x;
	r_pos.y += pos.y;
	g_shadowMap->Update(r_pos, m_position);


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