#pragma once
#include<Windows.h>

#define WINDOWWIDTH 924
#define WINDOWHEIGHT 750

class BitMapManager;

enum MYKEYVAL
{
	MYKEYVAL_UP,
	MYKEYVAL_DOWN,
	MYKEYVAL_LEFT,
	MYKEYVAL_RIGHT,
	MYKEYVAL_Z,
	MYKEYVAL_END,
};

enum SCENENUM
{
	SCENENUM_INTRO,
	SCENENUM_GAME
};

class Scene
{
protected:
	int m_updateCount;
	static BitMapManager* m_lpbitMapManager;

public:
	static void SetBitMapManager(BitMapManager* m_BitMapManager);
	virtual void InitScene(HDC& hdc) = 0;
	virtual void OperatorInput(MYKEYVAL key) = 0;
	virtual void Update() = 0;
	virtual SCENENUM Draw(HDC& hdc) = 0;

	Scene();
	virtual ~Scene();
};

