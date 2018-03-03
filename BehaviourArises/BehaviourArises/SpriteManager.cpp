#include "stdafx.h"
#include "SpriteManager.h"
#include "Sprite.h"


SpriteManager::SpriteManager(SDL_Renderer* p_renderer)
{
	m_renderer = p_renderer;
}
SpriteManager::~SpriteManager()
{
	m_sprites.clear();
	for(auto t: m_textures)
	{
		SDL_DestroyTexture(t.second);
		t.second = nullptr;
	}
	m_textures.clear();
}



Sprite* SpriteManager::CreateSprite(const std::string p_file, unsigned int p_x, unsigned int p_y, unsigned int p_w, unsigned int p_h)
{
	auto it = m_textures.find(p_file);
	if(it==m_textures.end())
	{
		SDL_Surface* surface = IMG_Load(p_file.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_FreeSurface(surface);
		m_textures[p_file] = texture;
		it = m_textures.find(p_file);
	}
	Sprite* sprite = new Sprite(it->second, p_x, p_y, p_w, p_h);
	m_sprites.push_back(sprite);
	return sprite;

}

void SpriteManager::DeleteSprite(Sprite* p_sprite)
{
	
	for (auto it = m_sprites.begin(); it != m_sprites.end();)
	{
		if (*it == p_sprite)
		{
			delete *it;
			it = m_sprites.erase(it);
		}
		else
		{
			it++;
		}
	}
	
}

