#pragma once
#include "BitMap.h"

enum ENEMYBMP
{
	ENEMYBMP_1,
	ENEMYBMP_1BACK,
	ENEMYBMP_1FRONT,
	ENEMYBMP_2,
	ENEMYBMP_2BACK,
	ENEMYBMP_2FRONT,
	ENEMYBMP_3,
	ENEMYBMP_3BACK,
	ENEMYBMP_3FRONT,
	ENEMYBMP_FIRE1,
	ENEMYBMP_FIRE2,
	ENEMYBMP_END,
};

enum BACKBMP
{
	BACKBMP_BACK,
	BACKBMP_DECO,
	BACKBMP_NORMAL1,
	BACKBMP_NORMAL2,
	BACKBMP_CASH,
	BACKBMP_LIFE,
	BACKBMP_MITER,
	BACKBMP_ENDOBJ,
	BACKBMP_END,
};

enum USERBMP
{
	USERBMP_1,
	USERBMP_2,
	USERBMP_3,
	USERBMP_DIE,
	USERBMP_WIN1,
	USERBMP_WIN2,
	USERBMP_END,
};

enum STARBMP
{
	STARBMP_1,
	STARBMP_2,
	STARBMP_3,
	STARBMP_END,
};

class BitMapManager
{
	BitMap m_enemyBitMap[ENEMYBMP_END];
	BitMap m_backBitMap[BACKBMP_END];
	BitMap m_userBitMap[USERBMP_END];
	BitMap m_starBitMap[STARBMP_END];
	
public:
	void Draw(HDC& hdc, ENEMYBMP enemyBitMap, int x, int y, int width = 0, int height = 0);
	void Draw(HDC& hdc, BACKBMP backBitMap, int x, int y, int width = 0, int height = 0);
	void Draw(HDC& hdc, USERBMP userBitMap, int x, int y, int width = 0, int height = 0);
	void Draw(HDC& hdc, STARBMP starBitMap, int x, int y, int width = 0, int height = 0);

	void InitBitMapManager(HDC& hdc);
	void Release();

	BitMapManager();
	~BitMapManager();
};




