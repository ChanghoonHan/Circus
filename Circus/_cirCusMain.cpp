#include <Windows.h>
#include <crtdbg.h>
#include "SceneManager.h"
#define VK_Z 0x5A

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char lpszClass[256] = "CIRCUS";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace,
	LPSTR lpszCmdParam, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(릭 번호);

	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;//통산 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//미리만들어놓은 브러쉬 가져옴
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;//프로시저 받아옴 메세지 재정의를 모아놓은 함수
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//윈도우 스타일

	RegisterClass(&WndClass);//os에 윈도우 등록

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		0, 0, 940, 789,
		NULL, (HMENU)NULL, hInstance, NULL);
	//CW_ ->x y wid hei
	//부모윈도우, idset, instand, NULL

	ShowWindow(hWnd, nCmdShow);//한번 그려옴

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);//메세지 번역 큐에서 가져와서 번역 파생처리
		DispatchMessage(&Message);//윈도우 프로시저가 콜 됨
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//핸들, 어떤메세지, 부가정보1, 부가정보2
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000 / 90, NULL);
		hdc = GetDC(hWnd);
		SceneManager::GetInstance()->InitSceneManager(hdc);
		return 0;
		break;

	case WM_TIMER:
		SceneManager::GetInstance()->InitScene();

		if (GetKeyState(VK_UP) & 0x8000)
		{
			SceneManager::GetInstance()->OperatorInput(MYKEYVAL_UP);
		}

		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			SceneManager::GetInstance()->OperatorInput(MYKEYVAL_DOWN);
		}

		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			SceneManager::GetInstance()->OperatorInput(MYKEYVAL_LEFT);
		}

		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			SceneManager::GetInstance()->OperatorInput(MYKEYVAL_RIGHT);
		}

		if (GetKeyState(VK_Z) & 0x8000)
		{
			SceneManager::GetInstance()->OperatorInput(MYKEYVAL_Z);
		}

		SceneManager::GetInstance()->Update();
		InvalidateRect(hWnd, NULL, false);
		return 0;
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SceneManager::GetInstance()->Draw(hdc);
		EndPaint(hWnd, &ps);
		return 0;
		break;

	case WM_DESTROY:
		SceneManager::GetInstance()->ReleaseSceneManagerVal();
		SceneManager::GetInstance()->ReleaseSceneManager();
		PostQuitMessage(0);//큐에 나간다는메세지 적재
		return 0;
		break;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));//기본 메세지처리..
}