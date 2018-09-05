#pragma once
#include "Enemy.h"

class EnemyFire :
	public Enemy
{

public:

	virtual void Init(bool isContinue);
	virtual int Update();
	virtual void Draw(HDC& hdc, bool isBackBit = false);

	EnemyFire();
	~EnemyFire();
};

