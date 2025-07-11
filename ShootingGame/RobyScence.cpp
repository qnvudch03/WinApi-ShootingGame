#include "pch.h"
#include "RobyScence.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Game.h"

void RobyScence::Init()
{
	_texture = ResourceManager::GetInstance()->GetTexture("Roby");
}

void RobyScence::Render(HDC hdc)
{
	_texture->Render(hdc, Vector(GWinSizeX / 2, GWinSizeY / 2));

	if (bIsVisible)
	{
		wstring scorestr = L"Press E";
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, GWinSizeX / 2 - 30, GWinSizeY / 1.5, scorestr.c_str(), scorestr.length());
	}
}

bool RobyScence::waitPressbutton()
{
	return InputManager::GetInstance()->GetButtonUp(KeyType::E);
}

void RobyScence::Destroy()
{
	ResourceManager::GetInstance()->Destroy();
}

void RobyScence::Update(float deltatTime)
{
	if (bIsVisible)
	{
		TextTimer += deltatTime;
	}

	else if (!bIsVisible)
	{
		TextTimer -= deltatTime;
	}

	if (TextTimer <= 0)
	{
		bIsVisible = true;
	}

	else if (TextTimer >= TextBlinkTime)
	{
		bIsVisible = false;
	}

	if (waitPressbutton())
	{
		Game::GetInstance()->InterGame();
	}
}