#pragma once
#include "singleTon.h"
#include "Scence.h"

class Game : public singleTon<Game>
{
	friend singleTon<Game>;
	
	Game() {}

public:
	void Init(HWND hwnd);

	void Update();

	void Render();

	HWND GetHwnd() { return _hwnd; }

	Scence* GetCurrentScence() { return currentScence; }

	void InterGame();

private:

	RECT _rect;
	HWND _hwnd;
	HDC _hdc;
	HDC _hdcBack;
	HBITMAP _bmpBack = {};

	Scence* currentScence = nullptr;
};

