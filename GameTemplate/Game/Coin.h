#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Player.h"
class Game;
class Player;
class Coin
{
public:
	Coin(CVector3 pos, CQuaternion rot,Player* player);
	~Coin();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 回転
	/// </summary>
	void Turn();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// コイン取得処理
	/// </summary>
	void CoinGet();
	bool GetCoinGet()
	{
		return CoinGetFlag;
	}
private:
	
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();             //座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();   //回転。
	Player* m_player = nullptr; //プレイヤー
	bool CoinGetFlag = false; //コイン取得フラグ
	Game* m_game = nullptr;

};

