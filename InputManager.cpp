#include "DXUT.h"
#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
	memcpy(Last, Current, sizeof(Current));

	for (int i = 0; i < 256; i++)
	{
		Current[i] = false;
		if (GetAsyncKeyState(i))
		{
			Current[i] = true;
		}
	}
}

bool InputManager::AnyGameKeyDown()
{
	for (int i = 0; i < 256; i++)
	{
		if (i == 'W' || i == 'A' || i == 'D' ||
			i == 'J' || i == 'K' || i == 'L')
		{
			if (Current[i] && !Last[i])
			{
				return true;
			}
		}
	}
	return false;
}

bool InputManager::AnyKeyDown()
{
	for (int i = 0; i < 256; i++)
	{

		if (i == 'A' || i == 'D')
		{
			return false;
		}
		if (Current[i] && !Last[i])
		{
			return true;
		}
	}
	return false;
}

bool InputManager::KeyDown(BYTE key)
{
	return Current[key] && !Last[key];
}

bool InputManager::KeyUp(BYTE key)
{
	return !Current[key] && Last[key];
}

bool InputManager::KeyPress(BYTE key)
{
	return Current[key] && Last[key];
}

Vector2 InputManager::GetMousePos()
{
	POINT pt = ptGetMousePos();
	return Vector2(pt.x, pt.y) -= Vector2(WINSIZEX / 2 - CAMERA->m_vCameraPos.x, WINSIZEY / 2 - CAMERA->m_vCameraPos.y);;
}

POINT InputManager::ptGetMousePos()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);
	return pt;
}
