#pragma once
#include "Enemy.h"
class EnemyBigRing :
	public Enemy
{

public:
	virtual void Init(bool isContinue);
	virtual int Update();
	virtual void Draw(HDC& hdc, bool isBackBit);

	EnemyBigRing();
	virtual ~EnemyBigRing();
};

