#pragma once
#include "BitMapManager.h"
#include "Scene.h"
#include "User.h"

enum ENEMYSTATE
{
	ENEMYSTATE_BACKWARD,
	ENEMYSTATE_FORWARD,
	ENEMYSTATE_STAY
};

class Enemy
{
protected:
	int m_posX;
	bool m_isFirstBitMap;
	ENEMYSTATE m_oldState;
	int m_updateCount;
	bool m_isLive;
	ENEMYSTATE m_state;
	RECT m_rect;
	RECT m_scoreRect;

	static User* m_lpUser;
	static BitMapManager* m_lpbitMapManager;

public:

	static void InitlpBitMapManagerAndlpUser(BitMapManager* bitMapManager, User* user);

	virtual void Init(bool isContinue = false) = 0;
	virtual int Update() = 0;
	virtual void Draw(HDC& hdc, bool isBackBit) = 0;

	void SetPosX(int x);
	RECT GetRect();
	RECT GetScoreRect();
	void Kill();
	bool IsLive();
	void InputOperator(MYKEYVAL key);


	Enemy();
	~Enemy();
};

