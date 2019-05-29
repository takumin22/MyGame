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
	m_model.Init(L"Assets/modelData/Chara_4Hero.cmo");
	m_model.SetAmbientLight(ambientColor);

	m_spjumpse.Init(L"Assets/sound/springjump.wav");

	//tkaファイルの読み込み。
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

	//アニメーションの初期化。
	m_animation.Init(
		m_model,			//アニメーションを流すスキンモデル。
							//これでアニメーションとスキンモデルが関連付けされる。
		m_animationClips,	//アニメーションクリップの配列。
		enAnimationClip_Num					//アニメーションクリップの数。
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
void Player::Move()
{

		auto MOVE_SPEED = 2500.0f;
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
			cameraForward *= lStick_y * MOVE_SPEED_JUMP * m_deltatime;
			cameraRight *= lStick_x * MOVE_SPEED_JUMP * m_deltatime;
		}
		else {
			cameraForward *= lStick_y * MOVE_SPEED * m_deltatime;
			cameraRight *= lStick_x * MOVE_SPEED * m_deltatime;
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
		m_moveSpeed.x += friction.x * m_deltatime;
		m_moveSpeed.z += friction.z * m_deltatime;
		//加速度を加える。
		m_moveSpeed += cameraForward;
		m_moveSpeed += cameraRight;
		m_moveSpeed.y += -1800.0f * m_deltatime;
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
	CVector3 move = CVector3::Zero();
    move.x = g_pad[0].GetLStickXF();
	move.z = g_pad[0].GetLStickYF();
	move.y = 0.0f;
	if ( m_charaCon.IsJump() == true) {
		m_animation.Play(enAnimationClip_jump,0.2);
	}
	else if (m_pstate) {
		if ( move.Length() > 0.7f ) {
			//走りモーション。
			m_animation.Play(enAnimationClip_run, 0.2f);
		}
		else if (move.Length() > 0.0001f || move.Length() < -0.0001) {
			//歩きモーション。
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
			//待機モーション
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
 //簡易的なAABB
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
		syoutotuflag = true;   // 衝突！！
	}
	else {
		syoutotuflag = false; //衝突していない
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
		syoutotuflag1 = true;   // 衝突！！
	}
	else {
		syoutotuflag1 = false; //衝突していない
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
		syoutotuflag2 = true;   // 衝突！！
	}
	else {
		syoutotuflag2 = false; //衝突していない
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
	case State_Idel: //待機ステート
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
			//入力がある。
			m_pstate = State_MoveRun;
		}
		if (g_pad[0].IsTrigger(enButtonB)) {
			m_pstate = State_Attack;
		}
		if (g_game->GetGoal() == true) {
			m_pstate = State_Goal;
		}
		if (m_position.y <= -500.0f) {
			//プレイヤーをスタート位置に戻す
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
			//入力がなくなった。
			m_pstate = State_Idel;
		}
		 if (g_pad[0].IsTrigger(enButtonA)) {
			//この時点でのXZ方向の速度を記憶しておく。
			m_moveSpeedWhenStartJump = m_moveSpeed.Length();
			m_moveSpeed.y = JUMP_SPEED;
			m_pstate = State_Jump;
		}
		if (g_pad[0].IsTrigger(enButtonB)) {
			m_pstate = State_Attack;
		}
		if (m_position.y <= -500.0f) {
			//プレイヤーをスタート位置に戻す
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
				//入力がなくなった。
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
	case State_SpringJump: //バネジャンプ
		m_spjumpse.Play(false);
		m_moveSpeed.y += 1300.0f;
		m_pstate = State_Idel;
		break;
	case State_Return://スタートに戻る
		PlayerPosRetrun();
		m_moveSpeed.y = 0.0f;
		DamageCount = 0;
		m_pstate = State_Idel;
		break;
	case State_Scaffold://足場上
	    Move();
		Scafflod();
	if (m_scaffold[1]->GetState() == m_scaffold[1]->State_FrontMove) {
		m_position.z -= 5.0f;

    }
	else if (m_scaffold[1]->GetState() == m_scaffold[1]->State_BackMove) {
		m_position.z += 5.0f;
	}
	if (g_pad[0].IsTrigger(enButtonA)) {
		//この時点でのXZ方向の速度を記憶しておく。
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
			//この時点でのXZ方向の速度を記憶しておく。
			m_moveSpeedWhenStartJump = m_moveSpeed.Length();
			m_moveSpeed.y = JUMP_SPEED;
			//m_pstate = State_Jump;
		}
		m_charaCon.SetPosition(m_position);
		break;
	case State_Damage: //ダメージ(仮)
		Time++;
		Move();
		
		 if (Time == 30.0f) {
			 m_pstate = State_InvincibleCount;
		 }
		break;
	case State_InvincibleCount:  //無敵時間(仮)	
		Move();
		Time++;
		if (g_pad[0].IsTrigger(enButtonA)) {
			m_moveSpeed.y = JUMP_SPEED;
		}
		if (Time== 60.0f) {
			m_pstate = State_Idel;
		}
		break;
	case State_Deth:  //死亡
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