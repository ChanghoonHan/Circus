#include "User.h"

void User::ChageUserBitMap()
{
	if (m_userState == USERSTATE_WIN)
	{
		if (m_UpdateCount % 5 == 0)
		{
			m_nowUserBitMap = (USERBMP)(((m_nowUserBitMap + 1) % 2) + 4);
		}
		return;
	}

	if (m_isJumping)
	{
		m_nowUserBitMap = USERBMP_3;
		return;
	}

	switch (m_userState)
	{
	case USERSTATE_STAY:
		m_isMovingForward = false;
		m_isMovingBackward = false;
		m_nowUserBitMap = USERBMP_1;
		break;

	case USERSTATE_FORWARD:
		if (m_UpdateCount % 5 == 0)
		{
			m_nowUserBitMap = (USERBMP)((m_nowUserBitMap + 1) % 3);
			if (m_nowUserBitMap == USERBMP_1)
			{
				m_userState = USERSTATE_STAY;
			}
		}
		break;

	case USERSTATE_BACKWARD:
		if (m_UpdateCount % 10 == 0)
		{
			m_nowUserBitMap = (USERBMP)((m_nowUserBitMap + 1) % 2);
			if (m_nowUserBitMap == USERBMP_1)
			{
				m_userState = USERSTATE_STAY;
			}
		}
		break;

	default:
		break;
	}
}

void User::Jump()
{
	m_userPos.y = 550 - (sin(getRadian(m_jumpSin)) * 200);
	m_jumpSin+=4;

	if (m_jumpSin > 181)
	{
		m_jumpSin = 0;
		m_userPos.y = 550;
		m_isJumping = false;
		m_userState = USERSTATE_STAY;
		m_nowUserBitMap = USERBMP_1;
		m_OnScoreText = false;
	}
}

void User::MoveForword()
{
	m_userPos.x += 5;

	if (!m_isJumping)
	{
		m_isMovingForward = false;
	}
}

void User::MoveBackword()
{
	m_userPos.x -= 5;

	if (!m_isJumping)
	{
		m_isMovingBackward = false;
	}

	m_CanMove = true;

	if (m_userPos.x < 100)
	{
		m_userPos.x = 100;
		m_CanMove = false;
	}
}

void User::OperatorInput(MYKEYVAL key, bool CanMove)
{
	if (m_userState == USERSTATE_WIN)
	{
		return;
	}

	switch (key)
	{
	case MYKEYVAL_LEFT:
		if (!m_isJumping)
		{
			if (CanMove)
			{
				m_CanMove = CanMove;
				m_isMovingBackward = true;
			}
			
			if (m_userState == USERSTATE_FORWARD)
			{
				m_isMovingBackward = false;
				m_isMovingForward = false;
				m_userState = USERSTATE_STAY;
				break;
			}
			m_userState = USERSTATE_BACKWARD;
		}
		break;

	case MYKEYVAL_RIGHT:
		if (!m_isJumping)
		{
			if (CanMove)
			{
				m_CanMove = CanMove;
				m_isMovingForward = true;
			}
			
			if (m_userState == USERSTATE_BACKWARD)
			{
				m_isMovingBackward = false;
				m_isMovingForward = false;
				m_userState = USERSTATE_STAY;
				break;
			}
			m_userState = USERSTATE_FORWARD;
		}
		else if (CanMove && !m_isMovingBackward)
		{
			m_CanMove = CanMove;
			m_isMovingForward = true;
		}
		break;

	case MYKEYVAL_Z:
		m_isJumping = true;
		break;
	default:
		break;
	}
}

void User::Update()
{
	m_UpdateCount++;
	if (m_UpdateCount == 1000)
	{
		m_UpdateCount = 0;
	}

	if (m_userState == USERSTATE_WIN)
	{
		ChageUserBitMap();
		m_OnScoreText = false;
		m_userPos.x += 1;
		if (m_userPos.x > WINDOWWIDTH - 205)
		{
			m_userPos.x = WINDOWWIDTH - 205;
		}
		m_userPos.y -= 1;
		if (m_userPos.y < 457)
		{
			m_userPos.y = 457;
		}
		return;
	}

	if (!m_isLive)
	{
		m_nowUserBitMap = USERBMP_DIE;
		return;
	}

	if (m_isJumping)
	{
		Jump();
	}

	ChageUserBitMap();

	if (m_isMovingForward)
	{
		MoveForword();
	}

	if (m_isMovingBackward)
	{
		MoveBackword();
	}

	SetRect(&m_lionRect, m_userPos.x + 30, m_userPos.y + 70, m_userPos.x + 105, m_userPos.y + 120);
	SetRect(&m_userRect, m_userPos.x + 33, m_userPos.y, m_userPos.x + 99, m_userPos.y + 70);
}

void User::Draw(HDC& hdc)
{
	if (m_OnScoreText)
	{
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, m_userPos.x + 56, 350, "500", strlen("500"));
		SetBkMode(hdc, OPAQUE);
	}
	m_lpbitMapManager->Draw(hdc, m_nowUserBitMap, m_userPos.x, m_userPos.y);
}

bool User::CheckCollisionWithOBJ(RECT rect, ENEMYTYPE enemy)
{
	RECT tempRect;
	bool isCollision = false;
	if (IntersectRect(&tempRect, &m_lionRect, &rect) ||
		IntersectRect(&tempRect, &m_userRect, &rect))
	{
		isCollision = true;
	}

	if (isCollision && enemy != ENEMYTYPE_FOOTBOARD && enemy != ENEMYTYPE_CASH && enemy != ENEMYTYPE_END)
	{
		m_isLive = false;
		m_nowUserBitMap = USERBMP_3;
		m_userState = USERSTATE_DIE;
	}
	else if (isCollision && enemy == ENEMYTYPE_CASH)
	{
		m_OnScoreText = true;
	}
	else if (isCollision && enemy == ENEMYTYPE_FOOTBOARD)
	{
		m_userState = USERSTATE_WIN;
	}

	return isCollision;
}

void User::Init(BitMapManager* bitMapManager)
{
	m_userState = USERSTATE_STAY;
	m_lpbitMapManager = bitMapManager;
	m_nowUserBitMap = USERBMP_1;
	m_isLive = true;
	m_OnScoreText = false;
	m_isMovingForward = false;
	m_isMovingBackward = false;
	m_isJumping = false;
	m_CanMove = false;
	m_UpdateCount = 0;
	m_jumpSin = 0;
	m_userPos.x = 100;
	m_userPos.y = 550;
	m_lionRect = { m_userPos.x + 30, m_userPos.y + 70, m_userPos.x + 105, m_userPos.y + 120 };
	m_userRect = { m_userPos.x + 33, m_userPos.y, m_userPos.x + 99, m_userPos.y + 70};
}

float User::getRadian(int num)
{
	return num * (PI / 180);
}

User::User()
{
}

User::~User()
{
}
