#pragma once
#include "physics/PhysicsStaticObject.h"
#include "Coin.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Player;
class Stage;
class Gate
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="player"></param>
	/// <param name="stage"></param>
	Gate(CVector3 pos, CQuaternion rot, Player* player, Stage* stage);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Gate();
/// <summary>
/// 更新
/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	void Open();
	/// <summary>
	/// ゲートのオープンフラグ
	/// </summary>
	/// <param name="flag">
	/// ture 開く
	/// false 開く動作停止
	/// </param>
	void SetOpenFlag(bool flag)
	{
		GateFlag = flag;
	}


private:
	SkinModel m_model;//モデルデータ
	CQuaternion m_rotation = CQuaternion::Identity();//回転
	CVector3 m_position = CVector3::Zero();             //座標
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CVector3 m_scale = CVector3::One();					//拡大率。
	PhysicsStaticObject m_phyStaticObject;      //静的物理オブジェクト
	Player* m_player = nullptr;
	bool GateFlag = false;//ゲートを開く際のフラグ
	Stage* m_stage;
	int GateHantei = 0;							//ゲートの当たり判定付け外し用
	CSoundSource m_opense;						//ゲートの開閉音
};

