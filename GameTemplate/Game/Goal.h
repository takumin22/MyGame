#pragma once
//#include "Stage.h"
class Player;
class Stage;
/// <summary>
/// 
/// </summary>
class Goal
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Goal();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Goal();
	/// <summary>
	/// ゴール取得判定
	/// </summary>
	void GoalGet();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// ゴールフラグを取得 
	/// </summary>
	/// <returns>trueならゴールしている</returns>
	bool GetGFlag()
	{
		return GetFlag;
	}
	void SetGoalFlag(bool flag)
	{
		GetFlag = flag;
	}
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	Player* m_player = nullptr;							//プレイヤー
	bool GetFlag = false;								//ゴールフラグ
	Stage* m_stage;										//ステージ
	Effekseer::Effect* m_starEffect = nullptr;
	Effekseer::Handle m_starEffectHandle = -1;
	bool flag = false;
	float srot = 2.0f;
	int StarTime = 0;
};

