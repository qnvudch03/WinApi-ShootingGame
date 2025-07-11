#pragma once
#include "singleTon.h"

enum class KeyState
{
	None,
	Press,		// 누르고 있는 중
	Down,		// 방금 누름
	Up,			// 방금 뗏음

	End
};

enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	SpaceBar = VK_SPACE,

	// 아이템 사용, 1,2
	KEY_1 = '1',
	KEY_2 = '2',

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	L = 'L',
	Q = 'Q',
	E = 'E',
	T = 'T',

	F1 = VK_F1,
	F2 = VK_F2,
};

constexpr int32 KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1;
// single
// inputmanager
// consoleGameIputmanager

class InputManager : public singleTon<InputManager>
{
	friend class singleTon<InputManager>;

private:
	InputManager() = default;


public:
	void init(HWND hwnd);
	void update();

	bool GetButtonPressed(KeyType key) { return GetState(key) == KeyState::Press; }

	// 맨 처음 눌렀을 때
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// 맨 처음 눌렀다가 땔 때
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	// 마우스 좌표 얻어오기
	POINT GetMousePos() { return _mousePos; }


private:
	HWND _hwnd = 0;	// 윈도우 핸들
	vector<KeyState> _states;
	POINT _mousePos = {};

private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }
};

