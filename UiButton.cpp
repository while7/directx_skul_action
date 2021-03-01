#include "DXUT.h"
#include "UiButton.h"

UiButton::UiButton(const string& bg_key, function<void()> callback, Vector2 size, Vector2 pos)
{
	button_bg = IMAGE->FindImage(bg_key);
	button_down_callback = callback;
	mouse = OBJECT->ObjList[MOUSE].front();

	this->pos = pos;
	this->size = size;

	button_col = new Collider(UI);
	button_col->UnEnable();
}

UiButton::~UiButton()
{
	SAFE_DELETE(button_col);
}

void UiButton::Enable()
{
	button_col->Enable();
}

void UiButton::UnEnable()
{
	button_col->UnEnable();
}

void UiButton::ButtonUpdate()
{
	button_col->SetRange(CAMERA->WorldToView(pos), button_bg->info.Width, button_bg->info.Height);

	if (button_col->isEnable)
	{
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			RECT rc2;
			if (IntersectRect(&rc2, &button_col->GetRect(), &mouse->col->GetRect()))
			{
				button_down_callback();
			}
		}
	}
}

void UiButton::ButtonRender()
{
	if (button_col->isEnable)
	{
		button_bg->CenterRender(pos, 0, size, 1);
	}
	button_col->Draw(0, 0, 255);
}