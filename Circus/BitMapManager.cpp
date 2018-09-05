#include "BitMapManager.h"

void BitMapManager::Draw(HDC& hdc, ENEMYBMP enemyBitMap, int x, int y, int width, int height)
{
	m_enemyBitMap[enemyBitMap].Draw(hdc, x, y, width, height);
}

void BitMapManager::Draw(HDC& hdc, BACKBMP backBitMap, int x, int y, int width, int height)
{
	m_backBitMap[backBitMap].Draw(hdc, x, y, width, height);
}

void BitMapManager::Draw(HDC& hdc, USERBMP userBitMap, int x, int y, int width, int height)
{
	m_userBitMap[userBitMap].Draw(hdc, x, y, width, height);
}

void BitMapManager::Draw(HDC& hdc, STARBMP starBitMap, int x, int y, int width, int height)
{
	m_starBitMap[starBitMap].Draw(hdc, x, y, width, height);
}

void BitMapManager::InitBitMapManager(HDC& hdc)
{
	m_enemyBitMap[ENEMYBMP_1].Init(hdc, "enemy.bmp");
	m_enemyBitMap[ENEMYBMP_1BACK].Init(hdc, "enemy_b.bmp");
	m_enemyBitMap[ENEMYBMP_1FRONT].Init(hdc, "enemy_f.bmp");
	m_enemyBitMap[ENEMYBMP_2].Init(hdc, "enemy1.bmp");
	m_enemyBitMap[ENEMYBMP_2BACK].Init(hdc, "enemy_1b.bmp");
	m_enemyBitMap[ENEMYBMP_2FRONT].Init(hdc, "enemy_1f.bmp");
	m_enemyBitMap[ENEMYBMP_3].Init(hdc, "enemy_l.bmp");
	m_enemyBitMap[ENEMYBMP_3BACK].Init(hdc, "enemy_l_b.bmp");
	m_enemyBitMap[ENEMYBMP_3FRONT].Init(hdc, "enemy_l_f.bmp");
	m_enemyBitMap[ENEMYBMP_FIRE1].Init(hdc, "front.bmp");
	m_enemyBitMap[ENEMYBMP_FIRE2].Init(hdc, "front2.bmp");

	m_backBitMap[BACKBMP_BACK].Init(hdc, "back.bmp");
	m_backBitMap[BACKBMP_DECO].Init(hdc, "back_deco.bmp");
	m_backBitMap[BACKBMP_NORMAL1].Init(hdc, "back_normal.bmp");
	m_backBitMap[BACKBMP_NORMAL2].Init(hdc, "back_normal2.bmp");
	m_backBitMap[BACKBMP_CASH].Init(hdc, "cash.bmp");
	m_backBitMap[BACKBMP_LIFE].Init(hdc, "icon.bmp");
	m_backBitMap[BACKBMP_MITER].Init(hdc, "miter.bmp");
	m_backBitMap[BACKBMP_ENDOBJ].Init(hdc, "end.bmp");

	m_userBitMap[USERBMP_1].Init(hdc, "player0.bmp");
	m_userBitMap[USERBMP_2].Init(hdc, "player1.bmp");
	m_userBitMap[USERBMP_3].Init(hdc, "player2.bmp");
	m_userBitMap[USERBMP_DIE].Init(hdc, "die.bmp");
	m_userBitMap[USERBMP_WIN1].Init(hdc, "win.bmp");
	m_userBitMap[USERBMP_WIN2].Init(hdc, "win2.bmp");

	m_starBitMap[STARBMP_1].Init(hdc, "star.bmp");
	m_starBitMap[STARBMP_2].Init(hdc, "star1.bmp");
	m_starBitMap[STARBMP_3].Init(hdc, "star2.bmp");
}

void BitMapManager::Release()
{
	for (size_t i = 0; i < ENEMYBMP_END; i++)
	{
		m_enemyBitMap[i].Release();
	}

	for (size_t i = 0; i < BACKBMP_END; i++)
	{
		m_backBitMap[i].Release();
	}

	for (size_t i = 0; i < USERBMP_END; i++)
	{
		m_userBitMap[i].Release();
	}

	for (size_t i = 0; i < STARBMP_END; i++)
	{
		m_starBitMap[i].Release();
	}
}

BitMapManager::BitMapManager()
{
}

BitMapManager::~BitMapManager()
{
}
