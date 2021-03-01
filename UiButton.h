#pragma once

class UiButton
{
public:
	UiButton(const string& bg_key, function<void()> callback, Vector2 size = { 1,1 }, Vector2 pos = center_vec2);
	~UiButton();

	void Enable();
	void UnEnable();

	void ButtonUpdate();
	void ButtonRender();
private:
public:
private:
	Object* mouse;
	texture* button_bg;
	Collider* button_col;
	function<void()> button_down_callback;
	Vector2 pos;
	Vector2 size;
};