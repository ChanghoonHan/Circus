#pragma once
#include "Scene.h"

enum STARBMP;

class IntroScene :
	public Scene
{
	bool m_isSelect;
	bool m_textOff;
	int m_textOnOffCount;
	HFONT m_newFont;
	HFONT m_oldFont;
	STARBMP m_startStar;

public:
	virtual void InitScene(HDC& hdc);
	virtual void OperatorInput(MYKEYVAL key);
	virtual void Update();
	virtual SCENENUM Draw(HDC& hdc);

	IntroScene();
	virtual ~IntroScene();
};

