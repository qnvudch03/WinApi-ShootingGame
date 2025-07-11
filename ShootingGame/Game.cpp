#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "GameScene.h"
#include "RobyScence.h"
#include "ResourceManager.h"

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	_hdcBack = ::CreateCompatibleDC(_hdc);

	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);

	InputManager::GetInstance()->init(hwnd);
	TimeManager::GetInstance()->Init();
	ResourceManager::GetInstance()->Init();

	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack); // DC�� BMP�� ����
	::DeleteObject(prev);

	//���� �ʱ�ȭ�� ���� ȭ������ ������ �ǰ�

	/*currentScence = new GameScene();
	currentScence->Init();*/

	currentScence = new RobyScence();
	currentScence->Init();

}

void Game::Update()
{
	InputManager::GetInstance()->update();
	TimeManager::GetInstance()->Update();

	/*if (currentScence != nullptr)
	{
		currentScence->Update(TimeManager::GetInstance()->GetDeltaTime());
	}*/

	//���簡 ���Ӿ��� ���
	if (currentScence == dynamic_cast<GameScene*>(currentScence))
	{
		currentScence->Update(TimeManager::GetInstance()->GetDeltaTime());
	}


	//���簡 ���Ӿ��� ���
	else if (currentScence == dynamic_cast<RobyScence*>(currentScence))
	{
		currentScence->Update(TimeManager::GetInstance()->GetDeltaTime());
	}
	
}

void Game::Render()
{
	/*if (currentScence != nullptr)
	{
		currentScence->Render(_hdcBack);
	}*/

	if (currentScence == dynamic_cast<GameScene*>(currentScence))
	{
		currentScence->Render(_hdcBack);
	}


	//���簡 ���Ӿ��� ���
	else if (currentScence == dynamic_cast<RobyScence*>(currentScence))
	{
		currentScence->Render(_hdcBack);
	}

	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);

	// ����Ʈ ���ۿ� ���簡 ��������, ����۴� �ʱ�ȭ
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}

void Game::InterGame()
{
	if (currentScence != nullptr)
	{
		delete currentScence;
		currentScence = nullptr;
	}
		
	
	currentScence = new GameScene();
	currentScence->Init();
}
