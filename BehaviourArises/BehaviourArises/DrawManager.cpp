#include "stdafx.h"
#include "DrawManager.h"
#include "Config.h"


DrawManager::DrawManager()
{
}


DrawManager::~DrawManager()
{
}

void DrawManager::Initialise()
{
	m_window = SDL_CreateWindow("5SD806: Behaviour Arises", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, 0);
	assert(m_window != nullptr && "SDL_CreateWindow FAILED!");

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_VIDEO_OPENGL);
	assert(m_renderer != nullptr && "SDL_CreateRenderer FAILED!");
	LoadFont(12);

}

void DrawManager::Destroy()
{	
	UnloadFont();
	
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;

	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	


}

void DrawManager::Clear()
{	
	SDL_SetRenderDrawColor(m_renderer, 25, 25, 25, 255);
	SDL_RenderClear(m_renderer);
}

void DrawManager::Present()
{
	SDL_RenderPresent(m_renderer);
}

void DrawManager::Draw(Sprite* p_sprite, int p_x, int p_y, int p_scale)
{
	SDL_Rect rect = { p_x,p_y, p_sprite->GetClip().w*p_scale, p_sprite->GetClip().h*p_scale };
	SDL_RenderCopy(m_renderer, p_sprite->GetTexture(), &p_sprite->GetClip(), &rect);
}

void DrawManager::DrawRect(SDL_Rect& p_rect, Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	SDL_SetRenderDrawColor(m_renderer, p_r, p_g, p_b, p_a);
	SDL_RenderDrawRect(m_renderer, &p_rect);
}

void DrawManager::DrawLine(int p_xPos, int p_yPos, int p_xTarget, int p_yTarget, Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	SDL_SetRenderDrawColor(m_renderer, p_r, p_g, p_b, p_a);
	SDL_RenderDrawLine(m_renderer, p_xPos, p_yPos, p_xTarget, p_yTarget);
}

void DrawManager::DrawText(int p_xPos, int p_Ypos, std::string p_text, SDL_Color p_color)
{
	if(m_defaultFont){
	SDL_Surface* surface = TTF_RenderText_Solid(m_defaultFont, p_text.c_str(), p_color);
	SDL_Rect* rect = new SDL_Rect;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	if (surface != nullptr)
	{
		rect->h = surface->h;
		rect->w = surface->w;
		rect->x = p_xPos;
		rect->y = p_Ypos;
		SDL_FreeSurface(surface);

	}
	SDL_RenderCopy(m_renderer, texture, NULL, rect);
	delete rect;
	rect = nullptr;
	SDL_DestroyTexture(texture);
	}

	else
	{
		LoadFont(12);
	}

}


SDL_Renderer* DrawManager::GetRenderer()
{
	return m_renderer;
}

SDL_Window* DrawManager::GetWindow()
{
	return m_window;
}

TTF_Font* DrawManager::GetDefFont()
{
	return m_defaultFont;
}


bool DrawManager::LoadFont(const int p_size)
{
	m_defaultFont = TTF_OpenFont("../External/fonts/VeraMono.ttf", p_size);

	return (m_defaultFont != nullptr);
}

void DrawManager::UnloadFont()
{
	if(m_defaultFont)
	{
		TTF_CloseFont(m_defaultFont);
	}
}

