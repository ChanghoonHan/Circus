#include "EnemySmallRing.h"

int EnemySmallRing::Update()
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

	SetRect(&m_rect, m_posX + 45, 513, m_posX + 55, 523);
	SetRect(&m_scoreRect, m_posX + 45, 0, m_posX + 55, 523);

	return m_posX;
}

void EnemySmallRing::Draw(HDC& hdc, bool isBackBit)
{
	if (!m_isLive)
	{
		return;
	}

	if (isBackBit)
	{
		m_lpbitMapManager->Draw(hdc, ENEMYBMP_3BACK, m_posX, 315);
	}
	else
	{
		m_lpbitMapManager->Draw(hdc, ENEMYBMP_3FRONT, m_posX+52, 315);
	}
}

void EnemySmallRing::Init(bool isContinue)
{
	if (m_isLive)
		return;

	m_isLive = true;
	m_isFirstBitMap = true;
	m_updateCount = 0;
	m_posX = WINDOWWIDTH - 50;
	SetRect(&m_rect, m_posX + 45, 513, m_posX + 55, 523);
}

EnemySmallRing::EnemySmallRing()
{
	Kill();
	Init(false);
	Kill();
}


EnemySmallRing::~EnemySmallRing()
{
}
