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

//todo 法線マップ。
ID3D11ShaderResourceView* g_normalMapSRV = nullptr;
//todo  ① スペキュラマップ
ID3D11ShaderResourceView* g_specMapSRV = nullptr;
Player::Player()
{

	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	m_model.SetAmbientLight(ambientColor);

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

	//todo Unityちゃんの法線マップをロード。
	//ファイル名を使って、テクスチャをロードして、ShaderResrouceViewを作成する。
	//todo Unityちゃんの法線マップをロード。
	//ファイル名を使って、テクスチャをロードして、ShaderResrouceViewを作成する。
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/utc_nomal.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_normalMapSRV);
	//Unityちゃんのスペキュラマップをロード。
	//ファイル名を使って、テクスチャをロードして、ShaderResourceViewを作成する。
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/utc_spec.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_specMapSRV);
	//モデルに法線マップを設定する。
	m_model.SetNormalMap(g_normalMapSRV);
	m_model.SetSpecularMap(g_specMapSRV);

	
	m_charaCon.Init(10.0f, 45.0f, m_position);
}


Player::~Player()
{
	//todo 法線マップを解放。
	if (g_normalMapSRV != nullptr) {
		g_normalMapSRV->Release();
	}
}
void Player::Move()
{

		auto MOVE_SPEED = 3500.0f;
		static float MOVE_SPEED_JUMP = 1000.0f;

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
		if (m_pstate == State_Jump) {
			//ジャンプ中でも緩く方向転換できるようにする。
			cameraForward *= lStick_y * MOVE_SPEED_JUMP * (1.0f / 60.0f);
			cameraRight *= lStick_x * MOVE_SPEED_JUMP * (1.0f / 60.0f);
		}
		else {
			cameraForward *= lStick_y * MOVE_SPEED * (1.0f / 60.0f);
			cameraRight *= lStick_x * MOVE_SPEED * (1.0f / 60.0f);
		}

		//摩擦力。
		auto friction = m_moveSpeed;
		if (m_pstate == State_Jump) {
			//ジャンプ中の摩擦力。
			friction *= -2.0f;
		}
		else {
			friction *= -5.0f;
		}
		m_moveSpeed.x += friction.x * (1.0f / 60.0f);
		m_moveSpeed.z += friction.z * (1.0f / 60.0f);
		//加速度を加える。
		m_moveSpeed += cameraForward;
		m_moveSpeed += cameraRight;
		m_moveSpeed.y += -1800.0f * (1.0f / 60.0f);
		if (m_pstate == State_Jump) {
			//移動速度に制限を加える。
			//ジャンプ中にジャンプ前より早くなることはない。
			auto moveSpeedXZ = CVector3(m_moveSpeed.x, 0.0f, m_moveSpeed.z);

			if (moveSpeedXZ.LengthSq() > m_moveSpeedWhenStartJump * m_moveSpeedWhenStartJump) {
				moveSpeedXZ.Normalize();
				moveSpeedXZ *= m_moveSpeedWhenStartJump;
				m_moveSpeed.x = moveSpeedXZ.x;
				m_moveSpeed.z = moveSpeedXZ.z;

			}
		}
				//m_moveSpeed.y -= 1800.0f * (1.0f / 60.0f);
				//キャラクターコントローラーに１フレームの経過時間:秒(第一引数)、時間ベースの移動速度(第二引数)を渡している。
				//Execute関数の中で行っている計算は下記のようなもの。
				//
				// CVector3 addPos = m_moveSpeed * ( 1.0f / 60.0f ); //１フレームで移動する量を計算する。
				// m_position += addPos;  //1フレームの移動量を座標に加算する。これをオイラー積分という。
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

	if (m_pstate == State_Jump) {
		m_animation.Play(enAnimationClip_jump, 0.1f);
	}
	else if (m_pstate == State_MoveRun
		|| m_pstate == State_Idel
		) {
		if (m_moveSpeed.Length() > 300.0f /** 300.0f*/) {
			//走りモーション。
			m_animation.Play(enAnimationClip_run, 0.2f);
		}
		else if (m_moveSpeed.Length() > 30.0f /** 30.0f*/) {
			//走りモーション。
			m_animation.Play(enAnimationClip_walk, 0.2f);
		}
		else {
			//待機モーション
			m_animation.Play(enAnimationClip_idle, 0.2f);
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
		static float JUMP_SPEED = 500.0f;
		Turn();
		AnimationControl();
	switch (m_pstate)
	{
	case State_Idel: //待機ステート
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
			//入力がある。
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
			//入力がなくなった。
			m_pstate = State_Idel;
		}
		else if (g_pad[0].IsTrigger(enButtonA)) {
			//この時点でのXZ方向の速度を記憶しておく。
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
				//入力がなくなった。
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
		Scafflod();
	if (m_scaffold[1]->m_sstate == m_scaffold[1]->State_FrontMove) {
		m_position.z -= 5.0f;

    }
	else if (m_scaffold[1]->m_sstate == m_scaffold[1]->State_BackMove) {
		m_position.z += 5.0f;
	}
	if (g_pad[0].IsTrigger(enButtonA)) {
		//この時点でのXZ方向の速度を記憶しておく。
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
			//この時点でのXZ方向の速度を記憶しておく。
			m_moveSpeedWhenStartJump = m_moveSpeed.Length();
			m_moveSpeed.y = JUMP_SPEED;
			m_pstate = State_Jump;
		}
		m_charaCon.SetPosition(m_position);
		break;
	case State_Damage: //ダメージ(仮)
		Time++;
		Move();
		 m_animation.Play(enAnimationClip_damage, 0.01f);
		 if (Time == 30.0f) {
			 m_pstate = State_InvincibleCount;
		 }
		break;
	case State_InvincibleCount:  //無敵時間(仮)	
		Move();
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
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
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

	//キャラクタを移動させる。
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