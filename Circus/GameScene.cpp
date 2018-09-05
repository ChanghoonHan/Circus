#include "GameScene.h"
#include "time.h"

void GameScene::OperatorInput(MYKEYVAL key)
{
	if (m_isGameUserDie || m_isGameClear || m_isGameStart)
	{
		return;
	}

	if (m_user.GetisJumping())
	{
		return;
	}

	switch (key)
	{
	case MYKEYVAL_LEFT:
		if (!m_user.GetCanMove())
		{
			m_isEndMap = false;
		}

		if (!m_user.GetisJumping())
		{
			if (m_backDecoState == BACKDECOSTATE_BACKWARD)
			{
				m_backDecoState = BACKDECOSTATE_STAY;
				break;
			}
			m_backDecoState = BACKDECOSTATE_FORWARD;
		}

		break;

	case MYKEYVAL_RIGHT:
		if (!m_user.GetisJumping())
		{
			if (m_backDecoState == BACKDECOSTATE_FORWARD)
			{
				m_backDecoState = BACKDECOSTATE_STAY;
				break;
			}
			m_backDecoState = BACKDECOSTATE_BACKWARD;
		}

		break;

	default:
		break;
	}

	m_user.OperatorInput(key, m_isEndMap);

	if (!m_user.GetisJumping() && !m_user.GetCanMove())
	{
		if (m_mapPos != 0)
		{
			for (size_t i = 0; i < ENEMYTYPE_END; i++)
			{
				if (m_enemy[i] != NULL)
				{
					m_enemy[i]->InputOperator(key);
				}
			}
		}
	}
}

void GameScene::Update()
{
	m_updateCount++;
	if (m_updateCount == 6000)
	{
		m_updateCount = 0;
	}

	if (m_isGameOver)
	{
		m_userDieTimeCount++;
		if (m_userDieTimeCount == 120)
		{
			m_isGameSceneEnd = true;
		}
		return;
	}

	if (m_isGameStart)
	{
		if (m_updateCount % 60 == 0)
		{
			m_isGameStart = !m_isGameStart;
			m_life--;
		}
		return;
	}

	if (m_isGameClear)
	{
		if (m_updateCount % 5 == 0)
		{
			m_backDecoWin = !m_backDecoWin;
		}

		m_bonusScore -= 10;
		if (m_bonusScore < 0)
		{
			FILE* file;
			file = fopen("highScore.txt", "w");
			fprintf(file, "%d", m_highScore);
			fclose(file);
			m_isGameSceneEnd = true;
			m_bonusScore = 0;
		}

		if (m_bonusScore != 0)
		{
			m_score += 10;
		}

		if (m_score >= m_highScore)
		{
			m_highScore = m_score;
		}

		m_user.Update();
		return;
	}

	if (m_isOnBetweenScene)
	{
		m_userDieTimeCount++;
		if (m_userDieTimeCount == 120)
		{
			InitGameForContinue();
		}
		return;
	}
	
	if (m_isGameUserDie)
	{
		m_userDieTimeCount++;
		if (m_userDieTimeCount == 60)
		{
			if (m_life == 0)
			{
				m_isGameOver = true;
				return;
			}

			m_isOnBetweenScene = true;
			return;
		}
		m_user.Update();
		return;
	}
	
	switch (m_backDecoState)
	{
	case BACKDECOSTATE_STAY:
		break;

	case BACKDECOSTATE_FORWARD:
		if (!m_isEndMap)
		{
			m_mapPos += 5;

			if (m_mapPos > 0)
			{
				m_mapPos = 0;
			}
		}

		break;

	case BACKDECOSTATE_BACKWARD:
		m_mapPos -= 5;

		if (m_mapPos < -(WINDOWWIDTH) * 9 - 220)
		{
			m_mapPos = -(WINDOWWIDTH) * 9 - 220;
			m_isEndMap = true;
		}

		break;
	default:
		break;
	}

	for (size_t i = 0; i < 10; i++)
	{
		int x = -((WINDOWWIDTH)* i) + 110;
		int y = -((WINDOWWIDTH)* (i + 1)) + 110;
		bool b = (m_mapPos <= x) && (m_mapPos > y);
		if (b == true)
		{
			m_mapCount = 10 - i;
			break;
		}
	}

	if (!m_user.GetisJumping())
	{
		if (m_isOverFire && m_isOverFireRing)
		{
			m_isOverFireRing = false;
			m_isOverFire = false;
			m_score += 400;
		}
		else
		{
			if (m_isOverFire)
			{
				m_isOverFire = false;
				m_score += 200;
			}
			if (m_isOverFireRing)
			{
				m_isOverFireRing = false;
				m_score += 100;
			}
		}
		

		m_backDecoState = BACKDECOSTATE_STAY;
	}
	else
	{
		if (m_backDecoState == BACKDECOSTATE_BACKWARD)
		{
			m_user.OperatorInput(MYKEYVAL_RIGHT, m_isEndMap);

			if (!m_isEndMap)
			{
				for (size_t i = 0; i < ENEMYTYPE_END; i++)
				{
					if (m_enemy[i] != NULL)
					{
						m_enemy[i]->InputOperator(MYKEYVAL_RIGHT);
					}
				}
			}
		}
		if (m_backDecoState == BACKDECOSTATE_FORWARD)
		{
			m_user.OperatorInput(MYKEYVAL_LEFT, m_isEndMap);

			if (!m_isEndMap)
			{
				for (size_t i = 0; i < ENEMYTYPE_END; i++)
				{
					if (m_enemy[i] != NULL)
					{
						m_enemy[i]->InputOperator(MYKEYVAL_LEFT);
					}
				}
			}

			if (!m_user.GetCanMove())
			{
				m_isEndMap = false;
			}
		}
	}

	int randNum = rand() % 10;

	int ringPos = m_enemy[ENEMYTYPE_BIGRING1]->Update();
	if (ringPos <= -264)
	{
		m_ringCount--;
	}

	if (ringPos <= 300 && m_ringCount == 1)
	{
		if (randNum < 2)
		{
			if (!m_enemy[ENEMYTYPE_SMALLRING]->IsLive())
			{
				m_enemy[ENEMYTYPE_CASH]->Init();
				m_enemy[ENEMYTYPE_SMALLRING]->Init();
			}
		}
		else
		{
			m_enemy[ENEMYTYPE_BIGRING2]->Init();
		}
		m_ringCount++;
	}

	ringPos = m_enemy[ENEMYTYPE_BIGRING2]->Update();
	if (ringPos <= -264)
	{
		m_ringCount--;
	}

	if (ringPos <= 300 && m_ringCount == 1)
	{
		if (randNum < 2)
		{
			if (!m_enemy[ENEMYTYPE_SMALLRING]->IsLive())
			{
				m_enemy[ENEMYTYPE_CASH]->Init();
				m_enemy[ENEMYTYPE_SMALLRING]->Init();
			}
		}
		else
		{
			m_enemy[ENEMYTYPE_BIGRING1]->Init();
		}
		m_ringCount++;
	}

	m_enemy[ENEMYTYPE_CASH]->Update();
	ringPos = m_enemy[ENEMYTYPE_SMALLRING]->Update();
	if (ringPos <= -264)
	{
		m_ringCount--;
	}

	if (ringPos <= 300 && m_ringCount == 1)
	{
		m_enemy[ENEMYTYPE_BIGRING1]->Init();
		m_ringCount++;
	}

	if (m_mapCount == m_mapCountForContinue - 1)
	{
		m_enemy[ENEMYTYPE_FIRE1]->Init();
	}

	int firePos = m_enemy[ENEMYTYPE_FIRE1]->Update();
	if (firePos < WINDOWWIDTH - 330 && m_mapCount == 1 && ((m_mapCountForContinue % 2) == 0))
	{
		m_enemy[ENEMYTYPE_FIRE1]->SetPosX(WINDOWWIDTH - 330);
	}

	if (firePos < 5)
	{
		m_enemy[ENEMYTYPE_FIRE2]->Init();
	}

	firePos = m_enemy[ENEMYTYPE_FIRE2]->Update();
	if (firePos < WINDOWWIDTH - 330 && m_mapCount == 1 && ((m_mapCountForContinue % 2) == 1))
	{
		m_enemy[ENEMYTYPE_FIRE2]->SetPosX(WINDOWWIDTH - 330);
	}

	if (firePos < 5)
	{
		m_enemy[ENEMYTYPE_FIRE1]->Init();
	}

	if (m_mapCount < 2)
	{
		m_enemy[ENEMYTYPE_FOOTBOARD]->Init();
	}
	m_enemy[ENEMYTYPE_FOOTBOARD]->Update();
	
	m_user.Update();
	CheckCollision();

	if (m_updateCount % 15 == 0)
	{
		m_bonusScore -= 10;
		if (m_bonusScore < 0)
		{
			m_bonusScore = 0;
		}
	}
}

SCENENUM GameScene::Draw(HDC& hdc)
{
	if (m_isGameOver)
	{
		Rectangle(hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT);
		m_backDeco.Draw(hdc, 0, 0, m_backDecoWin, false, true, m_score, m_highScore, m_bonusScore, m_life);
		if (m_isGameSceneEnd)
		{
			SelectObject(hdc, m_oldFont);
			return SCENENUM_INTRO;
		}
		return SCENENUM_GAME;
	}

	if (m_isOnBetweenScene)
	{
		Rectangle(hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT);
		m_backDeco.Draw(hdc, 0, 0, m_backDecoWin, true, false, m_score, m_highScore, m_bonusScore, m_life);
		return SCENENUM_GAME; 
	}

	Rectangle(hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT);
	HBRUSH m_oldBrush = (HBRUSH)SelectObject(hdc, m_greenBrush);
	Rectangle(hdc, 0, 316, WINDOWWIDTH, WINDOWHEIGHT);
	SelectObject(hdc, m_oldBrush);

	if (m_isGameSceneEnd)
	{
		Sleep(1000);
		return SCENENUM_INTRO;
	}
	else
	{
		for (size_t i = 0; i < 11; i++)
		{
			m_backDeco.Draw(hdc, m_mapPos + (WINDOWWIDTH*i), (10 - i) * 10, m_backDecoWin, false, false, m_score, m_highScore, m_bonusScore, m_life);
		}
	}

	for (size_t i = 0; i < ENEMYTYPE_END; i++)
	{
		if(m_enemy[i]!= NULL)
		{
			m_enemy[i]->Draw(hdc, true);
		}
	}
	m_user.Draw(hdc);

	

	for (size_t i = 0; i < ENEMYTYPE_END; i++)
	{
		if (m_enemy[i] != NULL && i != ENEMYTYPE_FOOTBOARD)
		{
			m_enemy[i]->Draw(hdc, false);
		}
	}
	
	return SCENENUM_GAME;
}

void GameScene::CheckCollision()
{
	bool isColl = false;

	if (m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_BIGRING1]->GetRect(), ENEMYTYPE_BIGRING1) ||
		m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_BIGRING2]->GetRect(), ENEMYTYPE_BIGRING2) ||
		m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_SMALLRING]->GetRect(), ENEMYTYPE_SMALLRING) ||
		m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_FIRE1]->GetRect(), ENEMYTYPE_FIRE1)||
		m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_FIRE2]->GetRect(), ENEMYTYPE_FIRE2))
	{
		isColl = true;
	}

	if (m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_BIGRING1]->GetScoreRect(), ENEMYTYPE_END) ||
		m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_BIGRING2]->GetScoreRect(), ENEMYTYPE_END) ||
		m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_SMALLRING]->GetScoreRect(), ENEMYTYPE_END))
	{
		m_isOverFireRing = true;
	}

	if (m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_FIRE1]->GetScoreRect(), ENEMYTYPE_END) ||
		m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_FIRE2]->GetScoreRect(), ENEMYTYPE_END))
	{
		m_isOverFire = true;
	}

	if (m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_CASH]->GetRect(), ENEMYTYPE_CASH))
	{
		m_score += 500;
		m_enemy[ENEMYTYPE_CASH]->Kill();
	}

	if (!isColl && m_user.CheckCollisionWithOBJ(m_enemy[ENEMYTYPE_FOOTBOARD]->GetRect(), ENEMYTYPE_FOOTBOARD))
	{
		m_isGameClear = true;
		for (size_t i = 0; i < ENEMYTYPE_END; i++)
		{
			if (i == ENEMYTYPE_FOOTBOARD || i == ENEMYTYPE_FIRE1 || i == ENEMYTYPE_FIRE2)
			{
				continue;
			}

			m_enemy[i]->Kill();
		}
		return;
	}

	if (isColl)
	{
		if (m_mapCount < 3)
		{
			m_mapCount++;
		}
		m_mapCountForContinue = m_mapCount;
		m_isGameUserDie = true;
		m_bonusScore = 5000;
	}
}

void GameScene::InitGameForContinue()
{
	for (size_t i = 0; i < ENEMYTYPE_END; i++)
	{
		m_enemy[i]->Kill();
		m_enemy[i]->Init();
		m_enemy[i]->Kill();
	}
	m_enemy[ENEMYTYPE_BIGRING1]->Init();

	/*if (m_mapCountForContinue == 1)
	{
		m_enemy[ENEMYTYPE_FOOTBOARD]->Init(true);
	}*/

	/*if (m_mapCountForContinue < 10)
	{
		m_enemy[ENEMYTYPE_FIRE1]->Init(true);
	}*/

	m_ringCount = 1;
	m_backDecoState = BACKDECOSTATE_STAY;
	m_user.Init(m_lpbitMapManager);
	m_updateCount = 0;
	m_backDecoWin = false;
	m_isEndMap = false;
	m_isGameClear = false;
	m_isGameUserDie = false;
	m_mapPos = 0;
	m_mapPos -= ((10 - m_mapCountForContinue) * WINDOWWIDTH);
	m_updateCount = 0;
	m_userDieTimeCount = 0;
	m_mapCount = 10;
	m_bonusScore = 5000;
	m_isOverFireRing = false;
	m_isOverFire = false;
	m_isGameStart = true;
	m_isOnBetweenScene = false;
}

void GameScene::InitScene(HDC& hdc)
{
	if (m_isFirstInit)
	{
		FILE* file;
		file = fopen("highScore.txt", "r");
		if (file == NULL)
		{
			m_highScore = 0;
		}
		else
		{
			fscanf(file, "%d", &m_highScore);
			fclose(file);
		}
		
		m_isFirstInit = false;
		Enemy::InitlpBitMapManagerAndlpUser(m_lpbitMapManager, &m_user);
		srand(time(NULL));
		m_newFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0,
				VARIABLE_PITCH | FF_ROMAN, "consolas");
		m_greenBrush = CreateSolidBrush(RGB(80, 160, 0));

		m_enemy[ENEMYTYPE_BIGRING1] = new EnemyBigRing;
		m_enemy[ENEMYTYPE_BIGRING2] = new EnemyBigRing;
		m_enemy[ENEMYTYPE_SMALLRING] = new EnemySmallRing;
		m_enemy[ENEMYTYPE_FIRE1] = new EnemyFire;
		m_enemy[ENEMYTYPE_FIRE2] = new EnemyFire;
		m_enemy[ENEMYTYPE_FOOTBOARD] = new FootBorad;
		m_enemy[ENEMYTYPE_CASH] = new EnemyCash;

		m_enemy[ENEMYTYPE_BIGRING1]->Init();
		m_backDeco.Init(hdc, m_lpbitMapManager);
	}
	
	m_oldFont = (HFONT)SelectObject(hdc, m_newFont);

	for (size_t i = 0; i < ENEMYTYPE_END; i++)
	{
		m_enemy[i]->Kill();
		m_enemy[i]->Init();
		m_enemy[i]->Kill();
	}

	m_user.Init(m_lpbitMapManager);
	m_enemy[ENEMYTYPE_BIGRING1]->Init();
	m_isGameSceneEnd = false;
	m_score = 0;
	m_ringCount = 1;
	m_backDecoState = BACKDECOSTATE_STAY;
	m_backDecoWin = false;
	m_isEndMap = false;
	m_isGameClear = false;
	m_isGameUserDie = false;
	m_mapPos = 0;
	//m_enemy[ENEMYTYPE_FOOTBOARD]->Init(true);//
	//m_enemy[ENEMYTYPE_FIRE1]->Init(true);//
	//m_mapPos -= ((10 - 1) * WINDOWWIDTH);//
	m_updateCount = 0;
	m_userDieTimeCount = 0;
	m_mapCount = 10;
	m_mapCountForContinue = 10;
	m_bonusScore = 5000;
	m_isOverFireRing = false;
	m_isOverFire = false;
	m_isGameStart = true;
	m_isOnBetweenScene = false;
	m_isGameOver = false;
	m_life = 4;
}

GameScene::GameScene()
{
	for (size_t i = 0; i < ENEMYTYPE_END; i++)
	{
		m_enemy[i] = NULL;
	}
	m_newFont = NULL;
	m_greenBrush = NULL;
	m_isFirstInit = true;
}

GameScene::~GameScene()
{
	for (size_t i = 0; i < ENEMYTYPE_END; i++)
	{
		delete(m_enemy[i]);
	}
	DeleteObject(m_newFont);
	DeleteObject(m_greenBrush);
}
