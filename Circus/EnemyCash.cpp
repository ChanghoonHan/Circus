#include "EnemyCash.h"


int EnemyCash::Update()
{
	m_updateCount++;
	if (m_updateCount == 1000)
	{
		m_updateCount = 0;
	}

	switch (m_state)
	{
	case ENEMYSTATE_BACKWARD:
		m_posX += 3;
		m_state = ENEMYSTATE_STAY;
		break;

	case ENEMYSTATE_FORWARD:
		m_posX -= 7;
		m_state = ENEMYSTATE_STAY;
		break;

	case ENEMYSTATE_STAY:
		m_posX -= 2;
		break;

	default:
		break;
	}

	if (m_posX <= -237)
	{
		Kill();
	}

	if (m_updateCount % 5 == 0)
	{
		m_isFirstBitMap = !m_isFirstBitMap;
	}

	SetRect(&m_rect, m_posX, 365, m_posX + 50, 417);

	return m_posX;
}

void EnemyCash::Draw(HDC& hdc, bool isBackBit)
{
	if (!m_isLive)
	{
		return;
	}

	if (isBackBit)
	{
		m_lpbitMapManager->Draw(hdc, BACKBMP_CASH, m_posX, 365);
	}
	
}

void EnemyCash::Init(bool isContinue)
{
	if (m_isLive)
		return;

	m_isLive = true;
	m_isFirstBitMap = true;
	m_updateCount = 0;
	m_posX = WINDOWWIDTH - 28;
	SetRect(&m_rect, m_posX, 365, m_posX + 50, 417);
}

EnemyCash::EnemyCash()
{
	Kill();
	Init(false);
	Kill();
}


EnemyCash::~EnemyCash()
{
}
