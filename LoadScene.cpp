#include "DXUT.h"
#include "LoadScene.h"
#define maxcount 1

LoadScene::LoadScene()
{
}


LoadScene::~LoadScene()
{
}

void LoadScene::Init()
{
	CAMERA->Reset();
	strcpy(str, "loading");
	timer = new Timer;
	timer->setTimer(1);

#pragma region FirstLoading // 로딩씬 리소스 로딩
#pragma endregion
	//이미지 로드 
#pragma region SecondLoading // 게임 리소스 로딩

	//* player *//
	{
		ImageLoad("p_idle", "player/idle", 7);
		ImageLoad("p_walk", "player/walk1", 10);
		ImageLoad("p_dash", "player/dash", 7);
		ImageLoad("p_jump", "player/jump", 3);
		ImageLoad("p_fall", "player/fall", 3);
		ImageLoad("p_fall_repeat", "player/fall_repeat", 3);

		ImageLoad("p_attack_a", "player/attack_a", 5);
		ImageLoad("p_attack_b", "player/attack_b", 5);
		ImageLoad("p_attack_c", "player/attack_c", 5);
		ImageLoad("p_attack_d", "player/attack_d", 6);
		ImageLoad("p_attack_e", "player/attack_e", 5);

		ImageLoad("p_jump_attack", "player/jump_attack", 3);
		ImageLoad("p_jump_attack_land", "player/jump_attack_land", 3);

		ImageLoad("p_skill1", "player/skill1", 9);

		ImageLoad("p_skill2_charging", "player/skill2_charging", 7);
		ImageLoad("p_skill2_completed", "player/skill2_completed", 4);
		ImageLoad("p_skill2_incompleted", "player/skill2_incompleted", 2);

		ImageLoad("p_skill3_attack_a", "player/skill3_attack_a", 3);
		ImageLoad("p_skill3_attack_b", "player/skill3_attack_b", 5);
	}

	//* wizard *//
	{
		ImageLoad("w_idle", "wizard/idle", 6);
		ImageLoad("w_walk", "wizard/walk", 6);
		ImageLoad("w_jump", "wizard/jump", 3);
		ImageLoad("w_dash", "wizard/dash", 7);
		ImageLoad("w_fall", "wizard/fall", 2);
		ImageLoad("w_fall_repeat", "wizard/fall_repeat", 3);
		ImageLoad("w_skill1", "wizard/skill1", 8);
		ImageLoad("w_skill2", "wizard/skill2", 8);
		ImageLoad("w_skill3", "wizard/skill3", 8);
		ImageLoad("w_skill4", "wizard/skill4", 8);
	}

	//* article *//
	{
		ImageLoad("a_idle", "article/idle", 4);
		ImageLoad("a_walk", "article/walk", 8);
		ImageLoad("a_jump", "article/jump", 2);
		ImageLoad("a_dash", "article/dash", 2);
		ImageLoad("a_fall", "article/fall", 2);
		ImageLoad("a_fall_repeat", "article/fall_repeat", 3);
		ImageLoad("a_ca_charging", "article/charge_attack_charging", 2);
		ImageLoad("a_ca_completed", "article/charge_attack_completed", 4);
		ImageLoad("a_jump_attack", "article/jump_attack", 4);
	}

	//* hunter *//
	{
		ImageLoad("h_idle", "hunter/idle", 4);
		ImageLoad("h_walk", "hunter/walk", 7);
		ImageLoad("h_dash", "hunter/dash", 7);
		ImageLoad("h_jump", "hunter/jump", 2);
		ImageLoad("h_ca_prepare", "hunter/charge_attack_prepare", 3);
		ImageLoad("h_ca_anticipation", "hunter/charge_attack_anticipation", 3);
		ImageLoad("h_ca_charging", "hunter/charge_attack_charging", 2);
		ImageLoad("h_ca_charged", "hunter/charge_attack_charged", 2);
		ImageLoad("h_ca_completed", "hunter/charge_attack_completed", 2);
		ImageLoad("h_ca_incompleted", "hunter/charge_attack_incompleted", 3);
		ImageLoad("h_fall", "hunter/fall", 2);
		ImageLoad("h_fall_repeat", "hunter/fall_repeat", 2);
		ImageLoad("h_fs_ready", "hunter/fast_shot_ready", 4);
		ImageLoad("h_fs_attack", "hunter/fast_shot_attack", 3);
		ImageLoad("h_ss_ready", "hunter/slow_shot_ready", 5);
		ImageLoad("h_ss_attack", "hunter/slow_shot_attack", 2);
		ImageLoad("h_jump_attack", "hunter/jump_attack", 3);
	}

	//* boss *//
	{
		ImageLoad("b_appear", "boss/appear", 4);
		ImageLoad("b_attack_a", "boss/attack_a", 6);
		ImageLoad("b_attack_b", "boss/attack_b", 6);
		ImageLoad("b_attack_c", "boss/attack_c", 7);
		ImageLoad("b_dash", "boss/dash", 6);
		ImageLoad("b_diagonal", "boss/diagonal", 5);
		ImageLoad("b_diagonal_fin", "boss/diagonal_fin", 6);
		ImageLoad("b_disappear", "boss/disappear", 4);
		ImageLoad("b_idle", "boss/idle", 8);
		ImageLoad("b_rush", "boss/rush", 12);
		ImageLoad("b_slash_h", "boss/slash_h", 6);
		ImageLoad("b_slash_v", "boss/slash_v", 4);
		ImageLoad("slash", "slash");
	}

	ImageLoad("null", "boss/null", 3);

	ImageLoad("bg", "bg");
	ImageLoad("whitebar", "whitebar");
	ImageLoad("key_bg", "key_bg");
	ImageLoad("black", "black");
	ImageLoad("title", "title");
	ImageLoad("setting", "setting");
	ImageLoad("status", "status");
	ImageLoad("power", "power");
	ImageLoad("hp", "hp");
	ImageLoad("MousePoint", "MousePoint");
	ImageLoad("profile", "profile");

#pragma endregion
}

void LoadScene::Update()
{
	if (!Imagelist.empty())
	{
		auto info = Imagelist.front();
		IMAGE->AddImage(info.m_Key, info.m_Path);
		Imagelist.pop_front();
		ImageCount++;
	}
	if (!Anilist.empty())
	{
		auto info = Anilist.front();
		IMAGE->ADDVECIMAGE(info.m_Key, info.m_Path, info.m_Size);
		Anilist.pop_front();
		ImageCount++;
	}
	if (Anilist.empty() && Imagelist.empty())
	{
		SCENE->ChangeScene("TitleScene");
		//PostQuitMessage(0);
	}
}

void LoadScene::Render()
{
	IMAGE->FindImage("Title")->CenterRender(center_vec2, 0, { 1.0f / 1.0390625f, 1.0f / 1.173611111111111f });

	IMAGE->drawText(str, {100,center_vec2.y + 200}, 150, RGB(255, 255, 255), false);

	if (timer->Update())
	{
		if (strcmp(str, "loading...") == 0)
		{
			strcpy(str, "loading");
		}
		strcat(str, ".");
	}
}

void LoadScene::Release()
{
	SAFE_DELETE(timer);
}

void LoadScene::ImageLoad(const string & _Key, const string & _Path, int size)
{
	if (size == 0)
	{
		Imagelist.push_back(Load(_Key, _Path));
		maxImageCount++;
	}
	else
	{
		Anilist.push_back(Load(_Key, _Path, size));
		maxImageCount++;
	}
}
