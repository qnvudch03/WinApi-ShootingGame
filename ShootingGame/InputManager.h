#pragma once
#include "singleTon.h"

enum class KeyState
{
	None,
	Press,		// ������ �ִ� ��
	Down,		// ��� ����
	Up,			// ��� ����

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

	// ������ ���, 1,2
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

	// �� ó�� ������ ��
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// �� ó�� �����ٰ� �� ��
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	// ���콺 ��ǥ ������
	POINT GetMousePos() { return _mousePos; }


private:
	HWND _hwnd = 0;	// ������ �ڵ�
	vector<KeyState> _states;
	POINT _mousePos = {};

private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }
};

