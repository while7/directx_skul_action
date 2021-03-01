#include "DXUT.h"
#include "UiWindow.h"

int UiWindow::REF_COUNT = 0;

UiWindow::UiWindow(const string& bg_key, BYTE key, Vector2 size, Vector2 pos)
	: window_open_key(key), window_bg(), window_size(size), window_pos(pos)
{
	open_flag = false;
	window_bg = IMAGE->FindImage(bg_key);
}

UiWindow::~UiWindow()
{
	for (auto& iter : button_list)
	{
		if (iter != nullptr)
			SAFE_DELETE(iter);
	}
	button_list.clear();
}

void UiWindow::WindowSwitch()
{
	open_flag = !open_flag;
	OBJECT->ObjList[MOUSE].front()->col->isEnable = !OBJECT->ObjList[MOUSE].front()->col->isEnable;
}

void UiWindow::WindowUpdate()
{
	if (open_flag)
	{
		for (auto& iter : button_list)
		{
			if (iter != nullptr)
			{
				iter->Enable();
				iter->ButtonUpdate();
			}
		}
	}
	else
	{
		for (auto& iter : button_list)
		{
			if (iter != nullptr)
			{
				iter->UnEnable();
			}
		}
	}

	if (INPUT->KeyDown(window_open_key))
	{
		open_flag = !open_flag;
		OBJECT->ObjList[MOUSE].front()->col->isEnable = !OBJECT->ObjList[MOUSE].front()->col->isEnable;
	}
}

void UiWindow::WindowRender()
{
	if (open_flag)
	{
		window_bg->CenterRender(window_pos, 0, window_size, 1);

		for (auto& iter : button_list)
		{
			if (iter != nullptr)
				iter->ButtonRender();
		}
	}
}

void UiWindow::AddButton(UiButton* btn)
{
	button_list.emplace_back(btn);
}

bool UiWindow::isOpen()
{
	return open_flag;
}
