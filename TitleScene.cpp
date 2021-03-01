#include "DXUT.h"
#include "TitleScene.h"

void TitleScene::Init()
{
	CAMERA->m_vCameraPos = center_vec2;
	bg = IMAGE->FindImage("title");
	key_bg = IMAGE->FindImage("key_bg");
	alpha = 255;
	down_flag = true;
	how_to_play_flag = false;
}

void TitleScene::Update()
{
	if (down_flag)
	{
		alpha -= 5;
	}
	else
	{
		alpha += 5;
	}
	if (alpha == 0)
	{
		if (down_flag)
		{
			down_flag = false;
		}
	}
	if (alpha == 255)
	{
		if (!down_flag)
		{
			down_flag = true;
		}
	}

	if (INPUT->AnyKeyDown())
	{
		if (!how_to_play_flag)
		{
			how_to_play_flag = true;
			bg = IMAGE->FindImage("black");
		}
		else
		{
			SCENE->ChangeScene("IngameScene");
		}
	}
}

void TitleScene::Render()
{
	if (!how_to_play_flag) // ㄹㅇ title
	{
		bg->CenterRender(center_vec2, 0, { 2.5f,2.8125f }, 1);

		IMAGE->drawText("아무키나 눌러 시작하세요 1트...", Vector2(center_vec2.x, center_vec2.y + 300), 50, RGBA(255, 255, 255, alpha), true);
	}
	else // 게임 설명
	{
		bg->CenterRender(center_vec2, 0, { 1,1 }, 1);

		IMAGE->drawText("[ 키 도움말 ]", Vector2(center_vec2.x, center_vec2.y - 300), 50, RGBA(255, 255, 255, alpha), true);

		Vector2 key_pos = {-325,-80};
		key_bg->CenterRender({ center_vec2.x + key_pos.x - 150,center_vec2.y + key_pos.y - 50 }, 0, { 4,4 }, 1);
		IMAGE->drawText("ESC", { center_vec2.x + key_pos.x - 150,center_vec2.y + key_pos.y - 50 }, 50, RGBA(255, 255, 255, 255), true);
		IMAGE->drawText("Pause", { center_vec2.x + key_pos.x - 150,center_vec2.y + key_pos.y - 150 }, 50, RGBA(255, 255, 255, alpha), true);

		key_bg->CenterRender({ center_vec2.x + key_pos.x + 150,center_vec2.y + key_pos.y }, 0, { 4,4 }, 1);
		IMAGE->drawText("W", { center_vec2.x + key_pos.x + 150,center_vec2.y + key_pos.y }, 80, RGBA(255, 255, 255, 255), true);
		IMAGE->drawText("Jump", { center_vec2.x + key_pos.x + 150,center_vec2.y + key_pos.y - 100 }, 50, RGBA(255, 255, 255, alpha), true);

		key_bg->CenterRender({ center_vec2.x + (key_pos.x - 125) + 150,center_vec2.y + (key_pos.y + 125) }, 0, { 4,4 }, 1);
		IMAGE->drawText("A", { center_vec2.x + (key_pos.x - 125) + 150,center_vec2.y + (key_pos.y + 125) }, 80, RGBA(255, 255, 255, 255), true);
		IMAGE->drawText("Left", { center_vec2.x + (key_pos.x - 125) + 150,center_vec2.y + (key_pos.y + 125) + 100 }, 50, RGBA(255, 255, 255, alpha), true);

		key_bg->CenterRender({ center_vec2.x + (key_pos.x) + 150,center_vec2.y + (key_pos.y + 125) }, 0, { 4,4 }, 1);
		IMAGE->drawText("S", { center_vec2.x + (key_pos.x) + 150,center_vec2.y + (key_pos.y + 125) }, 80, RGBA(255, 255, 255, 255), true);
		IMAGE->drawText("Down", { center_vec2.x + (key_pos.x) + 150,center_vec2.y + (key_pos.y + 125) + 100 }, 50, RGBA(255, 255, 255, alpha), true);

		key_bg->CenterRender({ center_vec2.x + (key_pos.x + 125) + 150,center_vec2.y + (key_pos.y + 125) }, 0, { 4,4 }, 1);
		IMAGE->drawText("D", { center_vec2.x + (key_pos.x + 125) + 150,center_vec2.y + (key_pos.y + 125) }, 80, RGBA(255, 255, 255, 255), true);
		IMAGE->drawText("Right", { center_vec2.x + (key_pos.x + 125) + 10 + 150,center_vec2.y + (key_pos.y + 125) + 100 }, 50, RGBA(255, 255, 255, alpha), true);

		key_bg->CenterRender({ center_vec2.x + (key_pos.x + 500),center_vec2.y + (key_pos.y + 125) }, 0, { 4,4 }, 1);
		IMAGE->drawText("J", { center_vec2.x + (key_pos.x + 500),center_vec2.y + (key_pos.y + 125) }, 80, RGBA(255, 255, 255, 255), true);
		IMAGE->drawText("Attack", { center_vec2.x + (key_pos.x + 500),center_vec2.y + (key_pos.y + 125) - 100 }, 40, RGBA(255, 255, 255, alpha), true);

		key_bg->CenterRender({ center_vec2.x + (key_pos.x + 650),center_vec2.y + (key_pos.y + 125) }, 0, { 4,4 }, 1);
		IMAGE->drawText("K", { center_vec2.x + (key_pos.x + 650),center_vec2.y + (key_pos.y + 125) }, 80, RGBA(255, 255, 255, 255), true);
		IMAGE->drawText("Skill", { center_vec2.x + (key_pos.x + 650),center_vec2.y + (key_pos.y + 125) - 100 }, 40, RGBA(255, 255, 255, alpha), true);

		key_bg->CenterRender({ center_vec2.x + (key_pos.x + 800),center_vec2.y + (key_pos.y + 125) }, 0, { 4,4 }, 1);
		IMAGE->drawText("L", { center_vec2.x + (key_pos.x + 800),center_vec2.y + (key_pos.y + 125) }, 80, RGBA(255, 255, 255, 255), true);
		IMAGE->drawText("Dash", { center_vec2.x + (key_pos.x + 800),center_vec2.y + (key_pos.y + 125) - 100 }, 40, RGBA(255, 255, 255, alpha), true);

		IMAGE->drawText("아무키나 눌러 시작하세요 2트...", Vector2(center_vec2.x, center_vec2.y + 300), 50, RGBA(255, 255, 255, alpha), true);
	}
}

void TitleScene::Release()
{
}
