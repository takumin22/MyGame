#pragma once

//シーンのインターフェースクラス。
class IScene
{
public:
	IScene()
	{
	}

	virtual ~IScene()
	{
	}
	void SetSceneNo(int i)
	{
		m_sceneNo = i;
	}
	int GetSceneNo()
	{
		return m_sceneNo;
	}
	virtual void Update() = 0;
	virtual void Draw() = 0;
private:
	int m_sceneNo = 1;
};
extern IScene* g_currentScene;
