#pragma once
/// <summary>
/// フェイドクラス
/// </summary>
class Fade
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Fade();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Fade();
	/// <summary>
	/// フェイドの状態のEnum
	/// </summary>
	enum Fade_State
	{
		fadein,
		fadeout,
		idel
	};
	/// <summary>
	/// Update関数
	/// 状態変化でtrue
	/// </summary>
	void Update();
	/// <summary>
	/// Draw関数
	/// </summary>
	void Draw();
	/// <summary>
	/// フェードインに遷移
	/// </summary>
	/// <param name="taim">
	/// フェードにかける時間（1/taim）
	/// </param>
	void Fadein(float taim = 20.0f)
	{
		m_faderate = 1 / taim;
		m_fadestate = fadein;
	}
	/// <summary>
	/// フェードアウトに遷移
	/// </summary>
	/// <param name="taim">
	/// フェードにかける時間（1/taim）
	/// </param>
	void Fadeout(float taim = 20.0f)
	{
		m_faderate = 1 / taim;
		m_faderate *= -1;
		m_fadestate = fadeout;
	}
	/// <summary>
	/// フェードをやめてアイドルに遷移
	/// </summary>
	void Fadeidel()
	{
		m_faderate = 0.0f;
		m_fadestate = idel;
	}
	/// <summary>
	/// 現在の状態を取得
	/// </summary>
	/// <returns>
	/// 状態のEnum（Faid::Fade_State）
	/// </returns>
	const Fade_State GetState()
	{
		return m_fadestate;
	}
private:
	Sprite m_texture_fade;										//タイトルのフェイド用のリソース
	float m_faderate = 0.0f;									//フェイドをかける時間
	float m_toumei = 0.0f;										//フェイドの度合い
	Fade_State m_fadestate = idel;								//現在の状態
};
extern Fade* g_fade;
