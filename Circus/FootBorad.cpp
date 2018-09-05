#include "FootBorad.h"

int FootBorad::Update()
{
	if (!m_isLive)
	{
		return 0;
	}

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
		if (m_posX < WINDOWWIDTH - 210)
		{
			m_posX = WINDOWWIDTH - 210;
		}
		m_state = ENEMYSTATE_STAY;
		break;

	default:
		break;
	}

	if (m_posX <= 0)
	{
		Kill();
	}

	if (m_updateCount % 5 == 0)
	{
		m_isFirstBitMap = !m_isFirstBitMap;
	}

	SetRect(&m_rect, m_posX, 572, m_posX + 142, 663);
	return m_posX;
}

void FootBorad::Draw(HDC& hdc, bool isBackBit)
{
	if (!m_isLive)
	{
		return;
	}

	m_lpbitMapManager->Draw(hdc, BACKBMP_ENDOBJ, m_posX, 575);
}

void FootBorad::FootBorad::Init(bool isContinue)
{
	if (m_isLive)
		return;

	m_isLive = true;
	m_isFirstBitMap = true;
	m_updateCount = 0;
	if (isContinue)
	{
		m_posX = WINDOWWIDTH + 10;
	}
	else
	{
		m_posX = WINDOWWIDTH + 120;
	}
	SetRect(&m_rect, m_posX, 572, m_posX + 142, 663);
}

FootBorad::FootBorad()
{
	Kill();
	Init(false);
	Kill();
}


FootBorad::~FootBorad()
{
}
