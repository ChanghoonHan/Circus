#include "IntroScene.h"
#include "BitMapManager.h"

void IntroScene::OperatorInput(MYKEYVAL key)
{
	if (key == MYKEYVAL_Z)
	{
		m_isSelect = true;
	}
}

void IntroScene::Update()
{
	m_updateCount++;
	if (m_updateCount == 1000)
	{
		m_updateCount = 0;
	}

	if (m_updateCount % 5 == 0)
	{
		if (m_isSelect == true)
		{
			m_textOff = !m_textOff;
			m_textOnOffCount++;
		}
	}

	if (m_updateCount % 10 == 0)
	{
		m_startStar = (STARBMP)((m_startStar + 1) % 3);
	}
}

SCENENUM IntroScene::Draw(HDC& hdc)
{
	Rectangle(hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT);

	for (size_t i = 0; i < 16; i++)
	{
		m_lpbitMapManager->Draw(hdc, (STARBMP)((m_startStar + i) % 3), 
			((WINDOWWIDTH/2) - (30 * 8)) + (30 * i), 130);
	}
	for (size_t i = 0; i < 6; i++)
	{
		m_lpbitMapManager->Draw(hdc, (STARBMP)((m_startStar + i) % 3),
			(WINDOWWIDTH / 2) + (30 * 8), 160 + (30 * i));
	}
	for (size_t i = 0; i < 16; i++)
	{
		m_lpbitMapManager->Draw(hdc, (STARBMP)((m_startStar + i) % 3),
			((WINDOWWIDTH / 2) - (30 * 8)) + (30 * i), 130 + (30 * 7));
	}
	for (size_t i = 0; i < 6; i++)
	{
		m_lpbitMapManager->Draw(hdc, (STARBMP)((m_startStar + i) % 3),
			(WINDOWWIDTH / 2) - (30 * 9), 160 + (30 * i));
	}

	m_oldFont = (HFONT)SelectObject(hdc, m_newFont);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, (WINDOWWIDTH / 2) - (30 * 4) - 10, 180, "CIRCUS", strlen("CIRCUS"));
	TextOut(hdc, (WINDOWWIDTH / 2) - (30 * 2) - 10, 240, "TROUPE", strlen("TROUPE"));
	TextOut(hdc, (WINDOWWIDTH / 2) - (30 * 7) - 5, 400, "PLAYER SELECT", strlen("PLAYER SELECT"));
	if (!m_textOff)
	{
		TextOut(hdc, (WINDOWWIDTH / 2) - (30 * 9) + 5, 460, "ขั  1 PLAYER   A", strlen("ขั  1 PLAYER   A"));
	}
	else
	{
		TextOut(hdc, (WINDOWWIDTH / 2) - (30 * 9) + 5, 460, "ขั              ", strlen("ขั				"));
	}
	TextOut(hdc, (WINDOWWIDTH / 2) - (30 * 9) + 5, 520, "    1 PLAYER   B", strlen("    1 PLAYER   B"));
	TextOut(hdc, (WINDOWWIDTH / 2) - (30 * 9) + 5, 580, "    2 PLAYERS  A", strlen("    2 PLAYERS  A"));
	TextOut(hdc, (WINDOWWIDTH / 2) - (30 * 9) + 5, 640, "    2 PLAYERS  B", strlen("    2 PLAYERS  B"));
	SetBkMode(hdc, OPAQUE);
	SelectObject(hdc, m_oldFont);

	if (m_textOnOffCount == 10)
	{
		return SCENENUM_GAME;
	}

	return SCENENUM_INTRO;
}

void IntroScene::InitScene(HDC& hdc)
{
	m_textOnOffCount = 0;
	m_updateCount = 0;
	m_startStar = STARBMP_1;
	m_isSelect = false;
	m_textOff = false;

	if (m_newFont == NULL)
	{
		m_newFont = CreateFont(70, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, "consolas");
	}
}

IntroScene::IntroScene()
{  
	m_newFont = NULL;
}

IntroScene::~IntroScene()
{
	DeleteObject(m_newFont);
}
