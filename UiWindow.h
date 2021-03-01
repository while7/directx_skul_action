#pragma once

class UiWindow
{
public:
	UiWindow(const string& bg_key, BYTE key = VK_ESCAPE, Vector2 size = {1,1}, Vector2 pos = center_vec2);
	~UiWindow();

	void WindowSwitch();

	void WindowUpdate();
	void WindowRender();
	
	void AddButton(UiButton* btn);

	bool isOpen();
private:
public:
private:
	static int REF_COUNT;

	vector<UiButton*> button_list;

	BYTE window_open_key;
	texture* window_bg;
	Vector2 window_size;
	Vector2 window_pos;

	bool open_flag;
};