#include "SceneManager.h"

#define SAFE_DELETE(a) if((a) != NULL) delete (a); (a)= NULL;

SceneManager* SceneManager::S = NULL;

void SceneManager::OperatorInput(MYKEYVAL key)
{
	m_scenes[m_sceneNum]->OperatorInput(key);
}

void SceneManager::Draw(HDC& hdc)
{
	int sceneNum = m_scenes[m_sceneNum]->Draw(m_memDC);
	TransparentBlt(hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT, m_memDC, 0, 0, WINDOWWIDTH, WINDOWHEIGHT, RGB(255, 0, 255));

	if (sceneNum != m_sceneNum)
	{
		m_isSceneChage = true;
		m_sceneNum = sceneNum;
	}
}

void SceneManager::Update()
{
	m_scenes[m_sceneNum]->Update();
}

void SceneManager::InitScene()
{
	if (m_isSceneChage)
	{
		m_isSceneChage = false;
		m_scenes[m_sceneNum]->InitScene(m_memDC);
	}
}

void SceneManager::InitSceneManager(HDC& hdc)
{
	m_newBrush = CreateSolidBrush(RGB(0, 0, 0));
	m_memDC = CreateCompatibleDC(hdc);
	SetTextColor(m_memDC, RGB(255, 255, 255));
	m_newBitMap = CreateCompatibleBitmap(hdc, WINDOWWIDTH, WINDOWHEIGHT);
	m_oldBitMap = (HBITMAP)SelectObject(m_memDC, m_newBitMap);
	m_oldBrush = (HBRUSH)SelectObject(m_memDC, m_newBrush);
	m_isSceneChage = true;

	m_sceneNum = 0;
	m_bitMapManager.InitBitMapManager(m_memDC);
	Scene::SetBitMapManager(&m_bitMapManager);
	m_scenes[0] = new IntroScene;
	m_scenes[0]->InitScene(m_memDC);
	m_scenes[1] = new GameScene; 
	m_scenes[1]->InitScene(m_memDC);
}

void SceneManager::ReleaseSceneManagerVal()
{
	SelectObject(m_memDC, m_oldBitMap);
	SelectObject(m_memDC, m_oldBrush);
	DeleteDC(m_memDC);
	DeleteObject(m_newBitMap);
	DeleteObject(m_newBrush);
	m_bitMapManager.Release();
	SAFE_DELETE(m_scenes[0]);
	SAFE_DELETE(m_scenes[1]);
}

SceneManager* SceneManager::GetInstance()
{
	if (S == NULL)
	{
		S = new SceneManager;
	}

	return S;
}

void SceneManager::ReleaseSceneManager()
{
	SAFE_DELETE(S);
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
