#pragma once
class ScrollMap
{
public:
	ScrollMap(int num);
	virtual ~ScrollMap();
	int num;
	texture* Bg;
	texture* Bg2;
	texture* Bg3;
	texture* Bg4;
	texture* Bg5;

	float scroll;
	float scroll2;
	float scroll3;
	float scroll4;
	float scroll5;
	void Update(float speed);
	void Render();
};