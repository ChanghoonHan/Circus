#include "EnemyFire.h"

int EnemyFire::Update()
{
	m_updateCount++;
	if (m_updateCount == 1000)
	{
		m_updateCount = 0;
	}

	switch (m_state)
	{
	case ENEMYSTATE_BACKWARD:
		m_posX += 5;
		m_state = ENEMYSTATE_STAY;
		break;

	case ENEMYSTATE_FORWARD:
		m_posX -= 5;
		m_state = ENEMYSTATE_STAY;
		break;

	default:
		break;
	}

	if (m_posX <= -100)
	{
		Kill();
	}

	if (m_updateCount % 5 == 0)
	{
		m_isFirstBitMap = !m_isFirstBitMap;
	}

	SetRect(&m_rect, m_posX + 30, 600, m_posX + 70, 680);
	SetRect(&m_scoreRect, m_posX + 30, 0, m_posX + 70, WINDOWHEIGHT);
	return m_posX;
}

void EnemyFire::Draw(HDC& hdc, bool isBackBit)
{
	if (!m_isLive)
	{
		return;
	}

	if (m_isFirstBitMap)
	{
		m_lpbitMapManager->Draw(hdc, ENEMYBMP_FIRE1, m_posX, 580);
	}
	else
	{
		m_lpbitMapManager->Draw(hdc, ENEMYBMP_FIRE2, m_posX, 580);
	}
}

void EnemyFire::Init(bool isContinue)
{
	if (m_isLive)
		return;

	m_isLive = true;
	m_isFirstBitMap = true;
	m_updateCount = 0;
	if (isContinue)
	{
		m_posX = WINDOWWIDTH - 110;
	}
	else
	{
		m_posX = WINDOWWIDTH;
	}

	SetRect(&m_rect, m_posX + 30, 600, m_posX + 70, 680);
}

EnemyFire::EnemyFire()
{
	Kill();
	Init(false);
	Kill();
}


EnemyFire::~EnemyFire()
{
}
