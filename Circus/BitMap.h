#pragma once
#include <Windows.h>
#include <iostream>
#include <string.h>

using namespace std;

class BitMap
{
	HDC m_hdc;
	HBITMAP m_NBitMap;
	HBITMAP m_OBitMap;
	int m_imageWidth;
	int m_imageHeight;

public:
	void Draw(HDC& hdc, int x, int y, int width = 0, int height = 0);
	void Init(HDC& hdc, string bitMapName);
	void Release();

	BitMap();
	~BitMap();
};

