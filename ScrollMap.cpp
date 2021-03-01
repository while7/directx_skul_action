#include "DXUT.h"
#include "ScrollMap.h"


ScrollMap::ScrollMap(int num)
	:scroll(0), scroll2(0), scroll3(0), scroll4(0), scroll5(0),num(num)
{
	if (num == 1)
	{
		Bg = IMAGE->FindImage("Stage1Background");
		Bg2 = IMAGE->FindImage("Stage1Background2");
		Bg3 = IMAGE->FindImage("Stage1Background3");
		Bg4 = IMAGE->FindImage("Stage1Background4");
		Bg5 = IMAGE->FindImage("Stage1Background5");
	}
	else if (num == 2)
	{
		Bg = IMAGE->FindImage("Stage2Background");
		Bg2 = IMAGE->FindImage("Stage2Background2");
		Bg3 = IMAGE->FindImage("Stage2Background3");
	}
	
}


ScrollMap::~ScrollMap()
{
}

void ScrollMap::Update(float speed)
{
	scroll -= (speed + 100) * D_TIME;
	scroll2 -= (speed + 70) * D_TIME;
	scroll3 -= (speed + 50) * D_TIME;
	if (num == 1) {
		scroll4 -= (speed + 30) * D_TIME;
		scroll5 -= (speed)*D_TIME;
	}
	
}

void ScrollMap::Render()
{
	float bg1 = (int)scroll % Bg->info.Width;
	Bg->CenterRender(Vector2(WINSIZEX / 2 + bg1 - Bg->info.Width, WINSIZEY / 2));
	Bg->CenterRender(Vector2(WINSIZEX / 2 + bg1, WINSIZEY / 2));

	float bg2 = (int)scroll2 % Bg2->info.Width;
	Bg2->CenterRender(Vector2(WINSIZEX / 2 + bg2 - Bg2->info.Width, WINSIZEY / 2),0,Vector2(1,1));
	Bg2->CenterRender(Vector2(WINSIZEX / 2 + bg2, WINSIZEY / 2));

	float bg3 = (int)scroll3 % Bg3->info.Width;
	Bg3->CenterRender(Vector2(WINSIZEX / 2 + bg3 - Bg3->info.Width, WINSIZEY / 2));
	Bg3->CenterRender(Vector2(WINSIZEX / 2 + bg3, WINSIZEY / 2));
	if (num == 1) {
		float bg4 = (int)scroll4 % Bg4->info.Width;
		Bg4->CenterRender(Vector2(WINSIZEX / 2 + bg4 - Bg4->info.Width, WINSIZEY / 2));
		Bg4->CenterRender(Vector2(WINSIZEX / 2 + bg4, WINSIZEY / 2));

		float bg5 = (int)scroll5 % Bg5->info.Width;
		Bg5->CenterRender(Vector2(WINSIZEX / 2 + bg5 - Bg5->info.Width, WINSIZEY / 2));
		Bg5->CenterRender(Vector2(WINSIZEX / 2 + bg5, WINSIZEY / 2));
	}



}
