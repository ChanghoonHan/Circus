#pragma once
#include <Windows.h>
#include "BitMapManager.h"

class BackDeco
{
	HPEN m_bluePen;
	HPEN m_redPen;

	BitMapManager* m_lpbitMapManager;

public:
	void Init(HDC& hdc, BitMapManager* lpbitMapManager);
	void Draw(HDC& hdc, int x, int miter, bool m_backDecoWin, bool isBetweenGame, bool isGameOver,
		int score, int highScore, int bonusScore, int life);
	BackDeco();
	~BackDeco();
};

