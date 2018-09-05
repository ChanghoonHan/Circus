#include "EnemyBigRing.h"

int EnemyBigRing::Update()
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

	if (m_posX <= -264)
	{
		Kill();
	}

	if (m_updateCount % 5 == 0)
	{
		m_isFirstBitMap = !m_isFirstBitMap;
	}

	SetRect(&m_rect, m_posX + 45, 565, m_posX + 55, 575);
	SetRect(&m_scoreRect, m_posX + 45, 0, m_posX + 55, 575);
	return m_posX;
}

void EnemyBigRing::Draw(HDC& hdc, bool isBackBit)
{
	if (!m_isLive)
	{
		return;
	}

	if (isBackBit)
	{
		if (m_isFirstBitMap)
		{
			m_lpbitMapManager->Draw(hdc, ENEMYBMP_1BACK, m_posX, 315);
		}
		else
		{
			m_lpbitMapManager->Draw(hdc, ENEMYBMP_2BACK, m_posX, 315);
		}
	}
	else
	{
		if (m_isFirstBitMap)
		{
			m_lpbitMapManager->Draw(hdc, ENEMYBMP_1FRONT, m_posX+52, 315);
		}
		else
		{
			m_lpbitMapManager->Draw(hdc, ENEMYBMP_2FRONT, m_posX+50, 315);
		}
	}
}

void EnemyBigRing::Init(bool isContinue )
{
	if (m_isLive)
		return;

	m_isLive = true;
	m_isFirstBitMap = true;
	m_updateCount = 0;
	m_posX = WINDOWWIDTH - 50;
	SetRect(&m_rect, m_posX + 45, 565, m_posX + 55, 575);
}

EnemyBigRing::EnemyBigRing()
{
	Kill();
	Init(false);
	Kill();
}

EnemyBigRing::~EnemyBigRing()
{
}
