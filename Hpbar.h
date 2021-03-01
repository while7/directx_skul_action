#pragma once
class Hpbar
{
private:
	static int REF_COUNT;
	Object* owner;
	Vector2 pos;

	texture* hpbar;

	D3DXCOLOR color;
public:
	Hpbar(Object* owner, Vector2 pos, D3DXCOLOR color);
	~Hpbar();
	void HpbarRender(bool isBoss = false);
};