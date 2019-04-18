#pragma once
#include "Sprite.h"
class Player;
class HP
{
public:
	HP();
	~HP();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// ダメージカウントをセット
	/// </summary>
	/// <param name="k">ダメージ量</param>
	void SetDamageCount(int k)
	{
		DamageCount = k;
	}
private:
	Sprite m_hp;									//体力のスプライトデータ
	Sprite m_hp2;
	Sprite m_hp3;
	Sprite m_hp4;
	CVector3 m_hppos = { 300.0f,300.0f,0.0f };		//体力の表示ポジション
	CVector3 m_hppos2 = { 400.0f,300.0f,0.0f };
	CVector3 m_hppos3 = { 500.0f,300.0f,0.0f };
	CVector3 m_hppos4 = { 600.0f,300.0f,0.0f };
	Player* m_player = nullptr;						//プレイヤー
	int DamageCount = 0;							//ダメージカウント

};

