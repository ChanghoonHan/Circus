#include "BackDeco.h"
#include "Scene.h"

void myStrcat(char* str1, char* str2, int len)
{
	int str1len = strlen(str1);
	int str2len = strlen(str2);
	int num = 0;
	for (size_t i = str1len - str2len; i < str1len; i++)
	{
		str1[i] = str2[num++];
	}
}

void BackDeco::Init(HDC& hdc, BitMapManager* lpbitMapManager)
{
	if (m_bluePen == NULL)
	{
		m_bluePen = CreatePen(NULL, 5, RGB(0, 0, 100));
	}

	if (m_redPen == NULL)
	{
		m_redPen = CreatePen(NULL, 5, RGB(100, 0, 0));
	}

	m_lpbitMapManager = lpbitMapManager;
	
}

void BackDeco::Draw(HDC& hdc, int x, int miter, bool m_backDecoWin, bool isBetweenGame, bool isGameOver, int score, int highScore, int bonusScore, int life)
{
	HPEN oldPen = (HPEN)SelectObject(hdc, m_bluePen);
	MoveToEx(hdc, 80, 20, NULL);
	LineTo(hdc, WINDOWWIDTH - 80, 20);
	MoveToEx(hdc, 80, 140, NULL);
	LineTo(hdc, WINDOWWIDTH - 80, 140);
	MoveToEx(hdc, 75, 25, NULL);
	LineTo(hdc, 75, 45);
	MoveToEx(hdc, WINDOWWIDTH - 75, 25, NULL);
	LineTo(hdc, WINDOWWIDTH - 75, 45);
	MoveToEx(hdc, 75, 115, NULL);
	LineTo(hdc, 75, 135);
	MoveToEx(hdc, WINDOWWIDTH - 75, 115, NULL);
	LineTo(hdc, WINDOWWIDTH - 75, 135);
	MoveToEx(hdc, 70, 50, NULL);
	LineTo(hdc, 70, 110);
	MoveToEx(hdc, WINDOWWIDTH - 70, 50, NULL);
	LineTo(hdc, WINDOWWIDTH - 70, 110);

	(HPEN)SelectObject(hdc, m_redPen);
	MoveToEx(hdc, 90, 30, NULL);
	LineTo(hdc, WINDOWWIDTH - 90, 30);
	MoveToEx(hdc, 90, 130, NULL);
	LineTo(hdc, WINDOWWIDTH - 90, 130);

	MoveToEx(hdc, 85, 35, NULL);
	LineTo(hdc, 85, 55);
	MoveToEx(hdc, WINDOWWIDTH - 85, 35, NULL);
	LineTo(hdc, WINDOWWIDTH - 85, 55);

	MoveToEx(hdc, 85, 105, NULL);
	LineTo(hdc, 85, 125);
	MoveToEx(hdc, WINDOWWIDTH - 85, 105, NULL);
	LineTo(hdc, WINDOWWIDTH - 85, 125);

	MoveToEx(hdc, 80, 60, NULL);
	LineTo(hdc, 80, 100);
	MoveToEx(hdc, WINDOWWIDTH - 80, 60, NULL);
	LineTo(hdc, WINDOWWIDTH - 80, 100);
	SelectObject(hdc, oldPen);

	SetBkMode(hdc, TRANSPARENT);
	char num[20];
	sprintf(num, "%d", score);
	char scoreText[20] = "1P-000000";
	myStrcat(scoreText, num, strlen(num));

	sprintf(num, "%d", highScore);
	char highSoreText[20] = "HI-000000";
	myStrcat(highSoreText, num, strlen(num));

	sprintf(num, "%d", bonusScore);
	char bonusSoreText[20] = "BONUS-0000";
	myStrcat(bonusSoreText, num, strlen(num));

	TextOut(hdc, 100, 30, scoreText, strlen(scoreText));
	TextOut(hdc, 350, 30, highSoreText, strlen(highSoreText));
	TextOut(hdc, 600, 30, "STATGE-1", strlen("STATGE-1"));
	TextOut(hdc, 350, 80, bonusSoreText, strlen(bonusSoreText));

	if (isGameOver)
	{
		TextOut(hdc, WINDOWWIDTH/2 - 100, WINDOWHEIGHT/2, "GAME OVER", strlen("GAME OVER"));
		SetBkMode(hdc, OPAQUE);
		return;
	}

	if (isBetweenGame)
	{
		TextOut(hdc, WINDOWWIDTH / 2 - 100, WINDOWHEIGHT / 2, "STAGE - 1", strlen("STAGE - 1"));
		for (size_t i = 0; i < life; i++)
		{
			m_lpbitMapManager->Draw(hdc, BACKBMP_LIFE, WINDOWWIDTH - 130 - (i * 35), 90);
		}
		SetBkMode(hdc, OPAQUE);
		return;
	}

	SetBkMode(hdc, OPAQUE);

	for (size_t i = 0; i < life; i++)
	{
		m_lpbitMapManager->Draw(hdc, BACKBMP_LIFE, WINDOWWIDTH - 130 - (i * 35), 90);
	}

	for (size_t i = 0; i < 14; i++)
	{
		if (m_backDecoWin)
		{
			m_lpbitMapManager->Draw(hdc, BACKBMP_NORMAL2, x + (i * 66) - 4, 192);
		}
		else
		{
			m_lpbitMapManager->Draw(hdc, BACKBMP_NORMAL1, x + (i * 66), 188);
		}
	}

	for (size_t i = 0; i < 8; i++)
	{
		m_lpbitMapManager->Draw(hdc, BACKBMP_BACK, x + (i * 134), 316);
	}

	m_lpbitMapManager->Draw(hdc, BACKBMP_DECO, x + (4 * 66) - 4, 183);
	m_lpbitMapManager->Draw(hdc, BACKBMP_MITER, x + 20, 685);

	SetBkMode(hdc, TRANSPARENT);
	char buf[20];
	sprintf(buf, "%d", miter);
	RECT rect = { x + 60, 688, x + 130, 788 };
	DrawText(hdc, buf, strlen(buf), &rect, DT_RIGHT);
	SetBkMode(hdc, OPAQUE);
}

BackDeco::BackDeco()
{
	m_bluePen = NULL;
	m_redPen = NULL;
}


BackDeco::~BackDeco()
{
	DeleteObject(m_bluePen);
	DeleteObject(m_redPen);
}
