#include "Enemy.h"

User* Enemy::m_lpUser = NULL;
BitMapManager* Enemy::m_lpbitMapManager = NULL;

void Enemy::InitlpBitMapManagerAndlpUser(BitMapManager* bitMapManager, User* user)
{
	m_lpbitMapManager = bitMapManager;
	m_lpUser = user;
}

void Enemy::SetPosX(int x)
{
	m_posX = x;
}

RECT Enemy::GetScoreRect()
{
	if (!m_isLive)
	{
		return{ 0, 0, 0, 0 };
	}

	return m_scoreRect;
}

RECT Enemy::GetRect()
{
	if (!m_isLive)
	{
		return { 0, 0, 0, 0 };
	}

	return m_rect;
}

bool Enemy::IsLive()
{
	return m_isLive;
}

void Enemy::Kill()
{
	m_isLive = false;
}

void Enemy::InputOperator(MYKEYVAL key)
{
	switch (key)
	{
	case MYKEYVAL_LEFT:
		if (m_state == ENEMYSTATE_FORWARD)
		{
			m_state = ENEMYSTATE_STAY;
		}
		else
		{
			m_state = ENEMYSTATE_BACKWARD;
		}
		break;

	case MYKEYVAL_RIGHT:
		if (m_state == ENEMYSTATE_BACKWARD)
		{
			m_state = ENEMYSTATE_STAY;
		}
		else
		{
			m_state = ENEMYSTATE_FORWARD;
		}
		break;

	default:
		break;
	}
}

Enemy::Enemy()
{
	m_state = ENEMYSTATE_STAY;
}


Enemy::~Enemy()
{
}
