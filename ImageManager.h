#pragma once

#include "singleton.h"

struct texture
{
	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;
	
	texture(LPDIRECT3DTEXTURE9 texturePtr, D3DXIMAGE_INFO info)
		:texturePtr(texturePtr), info(info)
	{
	}
	
	void CenterRender(Vector2 pos, float rot = 0, Vector2 size = Vector2(1, 1), float depth = 0, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	
	void Render(Vector2 pos, float rot = 0, Vector2 size = Vector2(1, 1), RECT rect = { 0,0,0,0 }, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

	void CenterRenderView(Vector2 pos, float rot = 0, Vector2 size = Vector2(1, 1), RECT rect = { 0,0,0,0 }, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void RenderView(Vector2 pos, float rot = 0, Vector2 size = Vector2(1, 1), RECT rect = { 0,0,0,0 }, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	
	void Release();
};

struct VECtexture {
	vector<texture *> m_VecTex;
public:
	VECtexture();
	~VECtexture();

	int GetSize();
	void ADDIMAGE(texture* tempImage);
	texture* FINDIMAGE(int count = -1);
};


class ImageManager : public singleton <ImageManager>
{
private:
	LPD3DXSPRITE m_sprite;
	map<string, texture*> m_images;
	map<string, VECtexture*> vecImages;

	LPD3DXFONT lpFont;

private:
	void Init();
	void Release();
public:
	ImageManager();
	~ImageManager();


	texture* AddImage(const string& key, const string& path, const int& number = 0);
	texture* FindImage(const string& key);

	VECtexture* ADDVECIMAGE(const string& key, const string& path, int max);
	VECtexture* FINDVECIMAGE(const string& key);

	void Begin();
	void End();

	void CenterRender(texture* texturePtr, Vector2 pos, float rot = 0, Vector2 size = Vector2(1, 1), float depth = 0, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void Render(texture* texturePtr, Vector2 pos, float rot = 0, Vector2 size = Vector2(1, 1), RECT rect = { 0,0,0,0 }, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRenderView(texture* texturePtr, Vector2 pos, float rot = 0, Vector2 size = Vector2(1, 1), RECT rect = {0,0,0,0}, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void RenderView(texture* texturePtr, Vector2 pos, float rot = 0, Vector2 size = Vector2(1, 1), RECT rect = { 0,0,0,0 }, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

	void drawText(const string& str, Vector2 pos, float size, D3DCOLOR color, bool Center);
	void drawTextView(const string& str, Vector2 pos, float size, D3DCOLOR color, bool Center);

	void LostDevice();
	void ResetDevice();

};

#define IMAGE ImageManager::GetInstance()