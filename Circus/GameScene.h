#pragma once
#include "Scene.h"
#include "User.h"
#include "Enemy.h"
#include "EnemyBigRing.h"
#include "EnemySmallRing.h"
#include "EnemyFire.h"
#include "FootBorad.h"
#include "BackDeco.h"
#include "EnemyCash.h"

enum BACKDECOSTATE
{
	BACKDECOSTATE_STAY,
	BACKDECOSTATE_FORWARD,
	BACKDECOSTATE_BACKWARD,
};

enum ENEMYTYPE;

class GameScene :
	public Scene
{
	HBITMAP m_backBitMap;
	HBRUSH m_greenBrush;
	User m_user;

	HFONT m_newFont;
	HFONT m_oldFont;

	Enemy* m_enemy[ENEMYTYPE_END];

	BackDeco m_backDeco;
	bool m_isGameStart;
	bool m_isGameUserDie;
	bool m_isGameSceneEnd;
	bool m_isOnBetweenScene;
	bool m_isGameOver;
	bool m_isGameClear;
	bool m_backDecoWin;
	bool m_isEndMap;
	bool m_isOverFireRing;
	bool m_isOverFire;
	bool m_isFirstInit;
	int m_mapCountForContinue;
	int m_userDieTimeCount;
	int m_ringCount;
	int m_mapPos, m_mapCount;
	int m_bonusScore, m_score, m_highScore;
	int m_life;
	BACKDECOSTATE m_backDecoState;
	void CheckCollision();
	void InitGameForContinue();
public:
	virtual void InitScene(HDC& hdc);
	virtual void OperatorInput(MYKEYVAL key);
	virtual void Update();
	virtual SCENENUM Draw(HDC& hdc);

	GameScene();
	~GameScene();
};

