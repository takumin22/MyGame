#pragma once
class PlState
{
public:
	/// <summary>
	/// アニメーションのenum
	/// </summary>
	enum EnAnimationClip {
		enAnimationClip_idle,		//待機アニメーション。
		enAnimationClip_run,		//走りアニメーション。
		enAnimationClip_walk,		//歩きアニメーション。
		enAnimationClip_attack,		//歩きアニメーション。
		enAnimationClip_jump,		//ジャンプアニメーション。
		enAnimationClip_damage,		//ダメージアニメーション
		enAnimationClip_godown,		//ダウンアニメーション
		enAnimationClip_toptojump,
		enAnimationClip_salute,
		enAnimationClip_Num,		//アニメーションクリップの総数。
	};
	/// <summary>
	/// プレイヤーのステートのenum
	/// </summary>
	enum PState {
		State_Idel,					//基本状態(歩)
		State_Attack,				//攻撃状態。
		State_Damage,				//ダメージ状態
		State_InvincibleCount,		//無敵時間状態
		State_SpringJump,			//バネジャンプ状態
		State_Return,				//復帰状態
		State_Deth,				//死亡状態
		State_Goal					//ゴール時状態
	};
};

