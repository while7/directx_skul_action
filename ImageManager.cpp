#include "DXUT.h"
#include "ImageManager.h"

void texture::CenterRender(Vector2 pos, float rot, Vector2 size, float depth, D3DCOLOR color)
{
	IMAGE->CenterRender(this, pos, rot, size, depth, color);
}

void texture::Render(Vector2 pos, float rot, Vector2 size, RECT rect, D3DCOLOR color)
{
	IMAGE->Render(this, pos, rot, size, rect, color);
}

void texture::CenterRenderView(Vector2 pos, float rot, Vector2 size, RECT rect, D3DCOLOR color)
{
	IMAGE->CenterRenderView(this, pos, rot, size, rect, color);

}

void texture::RenderView(Vector2 pos, float rot, Vector2 size, RECT rect, D3DCOLOR color)
{
	IMAGE->RenderView(this, pos, rot, size, rect, color);

}

void texture::Release()
{
	SAFE_RELEASE(texturePtr);
}


ImageManager::ImageManager()
	:m_sprite(nullptr)
{
	Init();
}


ImageManager::~ImageManager()
{
	Release();
}

texture* ImageManager::AddImage(const string& key, const string& path, const int& number)
{
	auto find = m_images.find(key);
	if (find == m_images.end())
	{
		LPDIRECT3DTEXTURE9 texturePtr;
		D3DXIMAGE_INFO info;

		char ch[256];
		sprintf(ch, "./Resource/%s.png", path.c_str());

		if (D3DXCreateTextureFromFileExA(g_device, ch, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texturePtr) == S_OK)
		{
			texture* text = new texture(texturePtr, info);
			m_images.insert(make_pair(key, text));
			return text;
		}
#pragma region 로딩실패



#pragma endregion
		return nullptr;
	}

	return find->second;
}

texture* ImageManager::FindImage(const string& key)
{
	auto find = m_images.find(key);
	if (find == m_images.end()) return nullptr;
	return find->second;
}

VECtexture* ImageManager::ADDVECIMAGE(const string & key, const string & path, int max)
{
	auto find = vecImages.find(key);
	if (find != vecImages.end())
		return find->second;

	VECtexture* vec = new VECtexture();

	for (int i = 1; i <= max; i++)
	{
		LPDIRECT3DTEXTURE9 lpTexture;
		D3DXIMAGE_INFO info;

		char ch[256];
		sprintf(ch, "./Resource/Image/%s/(%d).png", path.c_str(), i);

		if (D3DXCreateTextureFromFileExA(g_device, ch, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
			D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &info, nullptr, &lpTexture) == S_OK)
		{
			texture * text = new texture(lpTexture, info);
			vec->ADDIMAGE(text);
		}

	}

	vecImages.insert(make_pair(key, vec));
	return vec;
}

VECtexture* ImageManager::FINDVECIMAGE(const string & key)
{
	return vecImages[key];
}

void ImageManager::Init()
{
#pragma region Load
#pragma endregion

	D3DXCreateSprite(g_device, &m_sprite);
}

void ImageManager::Release()
{
	for (auto iter : m_images)
	{
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	m_images.clear();

	for (auto iter : vecImages)
	{
		SAFE_DELETE(iter.second);
	}
	vecImages.clear();
	m_sprite->Release();
}

void ImageManager::Begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);

}

void ImageManager::End()
{
	m_sprite->End();

}

void ImageManager::CenterRender(texture* texturePtr, Vector2 pos, float rot, Vector2 size, float depth, D3DCOLOR color)
{
	if (texturePtr)
	{
		D3DXMATRIXA16 mat;
		Vector2 CenterPos = Vector2(texturePtr->info.Width / 2, texturePtr->info.Height / 2);
		pos -= CenterPos;

		D3DXMatrixTransformation2D(&mat, &CenterPos, 0, &size, &CenterPos, rot, &pos);
		mat._43 = depth;
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

void ImageManager::Render(texture* texturePtr, Vector2 pos, float rot, Vector2 size, RECT rect, D3DCOLOR color)
{
	if (texturePtr)
	{
		D3DXMATRIXA16 mat;
		Vector2 CenterPos = Vector2(0, 0);
		pos -= CenterPos;

		D3DXMatrixTransformation2D(&mat, &CenterPos, 0, &size, &CenterPos, rot, &pos);

		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, &rect, nullptr, nullptr, color);
	}
}

void ImageManager::CenterRenderView(texture * texturePtr, Vector2 pos, float rot, Vector2 size,RECT rect, D3DCOLOR color)
{
	if (texturePtr)
	{
		D3DXMATRIXA16 mat;
		mat *= CAMERA->GetMat();
		Vector2 CenterPos = Vector2(texturePtr->info.Width / 2, texturePtr->info.Height / 2);
		pos -= CenterPos;

		D3DXMatrixTransformation2D(&mat, &CenterPos, 0, &size, &CenterPos, rot, &pos);

		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

void ImageManager::RenderView(texture * texturePtr, Vector2 pos, float rot, Vector2 size, RECT rect, D3DCOLOR color)
{
	if (texturePtr)
	{
		D3DXMATRIXA16 mat;
		mat *= CAMERA->GetMat();
		Vector2 CenterPos = Vector2(0, 0);
		pos -= CenterPos;

		D3DXMatrixTransformation2D(&mat, &CenterPos, 0, &size, &CenterPos, rot, &pos);

		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, &rect, nullptr, nullptr, color);
	}
}


void ImageManager::drawText(const string& str, Vector2 pos, float size, D3DCOLOR color, bool Center)
{
	D3DXMATRIX mat;
	if (!Center) {
		D3DXCreateFontA(g_device, size, 0, 10, 1, FALSE, HANGEUL_CHARSET, 0, 0, 0, "Fixedsys", &lpFont);
		D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
	}
	else {
		D3DXCreateFontA(g_device, size, 0, 0, 1, FALSE, HANGEUL_CHARSET, 0, 0, 0, "Fixedsys", &lpFont);
		D3DXMatrixTranslation(&mat, pos.x - size * (str.size() * 0.25), pos.y - size / 2.f, 0);
	}

	m_sprite->SetTransform(&mat);
	lpFont->DrawTextA(m_sprite, str.c_str(), str.size(), nullptr, DT_NOCLIP, color);

	SAFE_RELEASE(lpFont);
}

void ImageManager::drawTextView(const string & str, Vector2 pos, float size, D3DCOLOR color, bool Center)
{
	D3DXMATRIX mat;
	mat *= CAMERA->GetMat();
	if (!Center) {
		D3DXCreateFontA(g_device, size, 0, 10, 1, FALSE, HANGEUL_CHARSET, 0, 0, 0, "Fixedsys", &lpFont);
		D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
	}
	else {
		D3DXCreateFontA(g_device, size, 0, 0, 1, FALSE, HANGEUL_CHARSET, 0, 0, 0, "Fixedsys", &lpFont);
		D3DXMatrixTranslation(&mat, pos.x - size * (str.size() * 0.25), pos.y - size / 2.f, 0);
	}

	m_sprite->SetTransform(&mat);
	lpFont->DrawTextA(m_sprite, str.c_str(), str.size(), nullptr, DT_NOCLIP, color);

	SAFE_RELEASE(lpFont);
}

void ImageManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void ImageManager::ResetDevice()
{
	m_sprite->OnResetDevice();

}


VECtexture::VECtexture()
{
}

VECtexture::~VECtexture()
{
	for (auto iter : m_VecTex) {
		iter->Release();
		SAFE_DELETE(iter);
	}
	m_VecTex.clear();
}

int VECtexture::GetSize()
{
	return m_VecTex.size();
}

void VECtexture::ADDIMAGE(texture* tempImage)
{
	m_VecTex.push_back(tempImage);
}

texture* VECtexture::FINDIMAGE(int count)
{
	if (count == -1)
		return m_VecTex[0];
	else
		return m_VecTex[count];
}
