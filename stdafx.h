#pragma once
#pragma comment(lib,"legacy_stdio_definitions.lib")
#pragma comment(lib,"dsound.lib")

#include <iostream>
#include <map>
#include <list>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <functional>
#include <cmath>
#include <thread>
#include <cstdarg>
#include <sstream>
#include <crtdbg.h>
#include <cstdlib>
#include <random>

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

using namespace std;

enum ObjectTag :char
{
	NONE_TAG,
	PLAYER,
	ENEMY,
	PATTACK,
	EATTACK,
	UI,
	MOUSE,
	BOSS,
	PLATFORM,
	END_TAG,
}typedef Tag;

enum class EnemyType
{
	Article,
	Hunter,
	Wizard,
	Boss,
};

#define g_device DXUTGetD3D9Device()
#define D_TIME DXUTGetElapsedTime() * Time::TimeScale
#define RGB D3DCOLOR_XRGB
#define RGBA D3DCOLOR_RGBA

#define REF_LAMDA_VOID [&]()->void
#define REF_LAMDA_BOOL [&]()->bool
#define REF_LAMDA_INT [&]()->int
#define REF_LAMDA_LONG [&]()->long
#define REF_LAMDA_FLOAT [&]()->float
#define REF_LAMDA_DOUBLE [&]()->double

const int WINSIZEX = 1280;
const int WINSIZEY = 720;

const bool draw_flag = true;

static bool isWindowed = true;

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
const Vector2 center_vec2 = { WINSIZEX / 2, WINSIZEY / 2 };

static void Debug(const char* str)
{
	OutputDebugStringA(str);
	OutputDebugStringA("\n");
}
template<typename T>
void Debug(const char* format, const T src...)
{
	char str[256];
	va_list args;
	va_start(args, format);	
	vsprintf(str, format, args);
	OutputDebugStringA(str);
	OutputDebugStringA("\n");
	va_end(args);
}

#include "ImageManager.h"
#include "Timer.h"
#include "CameraManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Time.h"
#include "Math.h"
#include "World.h"
#include "Animation.h"
#include "Skill.h"
#include "Combo.h"
#include "Effect.h"
#include "Hpbar.h"
#include "Profile.h"
#include "Charge.h"
#include "UiButton.h"
#include "UiWindow.h"
#include "Mouse.h"
#include "Patterns.h"