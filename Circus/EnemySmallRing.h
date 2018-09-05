#pragma once
#include "Enemy.h"
class EnemySmallRing :
	public Enemy
{
public:
	virtual void Init(bool isContinue);
	virtual int Update();
	virtual void Draw(HDC& hdc, bool isBackBit);

	EnemySmallRing();
	~EnemySmallRing();
};

