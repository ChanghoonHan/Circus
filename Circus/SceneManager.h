#pragma once
#include "Scene.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "BitMapManager.h"

class SceneManager
{
	HDC m_memDC;
	HBRUSH m_newBrush;
	HBRUSH m_oldBrush;
	HBITMAP m_newBitMap;
	HBITMAP m_oldBitMap;

	bool m_isSceneChage;

	int m_sceneNum;
	BitMapManager m_bitMapManager;
	Scene* m_scenes[2];

	static SceneManager* S;
	SceneManager();

public:
	void InitScene();
	void OperatorInput(MYKEYVAL key);
	void Draw(HDC& hdc);
	void Update();

	void InitSceneManager(HDC& hdc);
	void ReleaseSceneManagerVal();

	static SceneManager* GetInstance();
	static void ReleaseSceneManager();
	~SceneManager();
};

