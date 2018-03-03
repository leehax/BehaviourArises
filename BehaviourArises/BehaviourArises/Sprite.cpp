#include "stdafx.h"
#include "Sprite.h"



Sprite::Sprite(SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h)
{
	m_tex = p_tex;
	SetClip(p_x, p_y, p_w, p_h);
}

Sprite::~Sprite()
{
}

void Sprite::SetClip(int p_x, int p_y, int p_w, int p_h)
{
	m_clip.x = p_x;
	m_clip.y = p_y;
	m_clip.w = p_w;
	m_clip.h = p_h;

}

SDL_Rect Sprite::GetClip()
{
	return m_clip;
}

SDL_Texture* Sprite::GetTexture()
{
	return m_tex;
}