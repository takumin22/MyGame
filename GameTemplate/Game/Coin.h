#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Player/Player.h"
#include "Gate.h"

class Gate;
class Game;
class Player;
class Coin
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="player"></param>
	Coin(CVector3 pos, CQuaternion rot,Player* player);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Coin();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// コイン取得処理
	/// </summary>
	void CoinGet();
	/// <summary>
	/// コイン取得状態
	/// </summary>
	/// <returns>
	/// true 取得
	/// false　未取得
	/// </returns>
	bool GetCoinGet()
	{
		return CoinGetFlag;
	}
private:
	
	SkinModel m_model;									//モデルデータ
	CVector3 m_position = CVector3::Zero();             //座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();   //回転。
	CVector3 ambientColor = { 1.0f, 1.0f, 1.0f };		//環境光のカラー
	Player* m_player = nullptr;							//プレイヤー
	bool CoinGetFlag = false;							//コイン取得フラグ
	Effekseer::Effect* m_coinEffect = nullptr;
	Effekseer::Handle m_coinEffectHandle = -1;
	bool flag = false;
	float rotspeed = 10.0f;
	int CoinTime = 0;

};

