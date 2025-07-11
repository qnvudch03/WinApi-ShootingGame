#pragma once

#include <iostream>
#include <windows.h>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <functional>	// std::function
#include <algorithm>	// std::find_if, std::sort
#include <random>

// C++ 20
#include <format>		// std::format("x:{0}, y:{1}"
#include <numbers>  
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

// transparent Blt
#pragma comment(lib, "msimg32.lib")

using namespace std;

#define SAFE_DELETE(ptr)		\
	if (ptr)					\
	{							\
		delete ptr;				\
		ptr = nullptr;			\
	}

// �޸� ��. json ���̺귯�� ���ʿ��� �ؾ��� new Ű����� �浹���� �ʴ´�.
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

// ���� ����� 
#include "Defines.h"
