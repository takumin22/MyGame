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
	Goal();
	~Goal();
	/// <summary>
	/// ゴール取得判定
	/// </summary>
	void GoalGet();
	void Update();
	void Draw();
	/// <summary>
	/// ゴールフラグを取得 
	/// </summary>
	/// <returns>trueならゴールしている</returns>
	bool GetGFlag()
	{
		return GetFlag;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <remarks>
	/// </remarks>
	/// <param name="gflag"></param>
	void SetGFlag(bool gflag)
	{
		GetFlag = gflag;
	}
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();     //座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rotation = CQuaternion::Identity();  //回転。
	Player* m_player = nullptr;
	bool GetFlag = false;              //ゴールフラグ
	Stage* m_stage;
};

