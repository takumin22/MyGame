#pragma once

class sky
{
public:
	sky();
	~sky();
	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="mapfilepath">テクスチャーファイルパス(L"filepath")</param>
	/// <param name="modelfilePath">モデルファイルパス(L"filepath")</param>
	/// <param name="scale">スケール(CVector3)</param>
	void Init(const wchar_t* mapfilepath, const wchar_t* modelfilePath, CVector3 scale);
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	void Relese();
	/// <summary>
	/// ファイルからddsを作成する関数
	/// </summary>
	/// <param name="fileName">ファイルパス(L"filepath")</param>
	/// <returns>bool</returns>
	bool CreateFromDDSTextureFromFile(const wchar_t* fileName);
	/// <summary>
	/// スケールを再設定する関数
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ポジションをセットする関数
	/// </summary>
	/// <param name="pos">ポジション(CVector3)</param>
	void SetPositon(CVector3& pos)
	{
		m_position = pos;
	}

private:
	SkinModel			m_skinmodel;					//スキンモデル
	CVector3			m_scale;						//スケール
	CVector3			m_position = CVector3::Zero();	//ポジション
	ID3D11ShaderResourceView*	m_srv = nullptr;	//SRV
	bool						m_isValid = false;	//有効かどうかのフラグ
};

