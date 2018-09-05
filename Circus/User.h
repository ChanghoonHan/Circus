#pragma once
#include "BitMapManager.h"
#include "Scene.h"
#include <math.h>

#define PI 3.141592f

enum USERSTATE
{
	USERSTATE_STAY,
	USERSTATE_FORWARD,
	USERSTATE_BACKWARD,
	USERSTATE_DIE,
	USERSTATE_WIN,
};

enum ENEMYTYPE
{
	ENEMYTYPE_BIGRING1,
	ENEMYTYPE_BIGRING2,
	ENEMYTYPE_SMALLRING,
	ENEMYTYPE_FIRE1,
	ENEMYTYPE_FIRE2,
	ENEMYTYPE_FOOTBOARD,
	ENEMYTYPE_CASH,
	ENEMYTYPE_END,
};

class User
{
	POINT m_userPos;
	BitMapManager* m_lpbitMapManager;
	USERSTATE m_userState;
	USERBMP m_nowUserBitMap;
	RECT m_lionRect;
	RECT m_userRect;

	bool m_OnScoreText;
	bool m_isLive;
	bool m_isMovingForward;
	bool m_isMovingBackward;
	bool m_isJumping;

	bool m_CanMove;

	int m_UpdateCount;
	int m_jumpSin;

	float getRadian(int num);
	void ChageUserBitMap();
	void Jump();
	void MoveForword();
	void MoveBackword();

public:
	inline bool GetCanMove()
	{
		return m_CanMove;
	}
	inline bool GetisJumping()
	{
		return m_isJumping;
	}
	inline USERSTATE GetUserState()
	{
		return m_userState;
	}
	void Draw(HDC& hdc);
	void Init(BitMapManager* bitMapManager);
	void Update();
	void OperatorInput(MYKEYVAL key, bool isCanMove);
	bool CheckCollisionWithOBJ(RECT rect, ENEMYTYPE enemy);

	User();
	~User();
};

