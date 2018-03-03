#include "stdafx.h"
#include "Tile.h"
#include "DrawManager.h"

#include "ServiceLocator.h"
#include "World.h"
#include "SpriteManager.h"
#include <iostream>


Tile::Tile(int p_x, int p_y, int p_w, int p_h, int p_gridX, int p_gridY)
{
	m_rect = { p_x,p_y,p_w,p_h };
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_sprites.push_back(m_spriteManager->CreateSprite("../External/Textures/Spacedirt.png", 0, 0, 32, 32));
	m_sprites.push_back(m_spriteManager->CreateSprite("../External/Textures/Spacegrass.png", 0, 0, 32, 32));
	m_sprites.push_back(m_spriteManager->CreateSprite("../External/Textures/Crater.png", 0, 0, 32, 32));
	m_sprites.push_back(m_spriteManager->CreateSprite("../External/Textures/BlockedTile.png", 0, 0, 32, 32));

	m_gridX = p_gridX;
	m_gridY = p_gridY;
	m_x = p_x;
	m_y = p_y;
	int randomtype = rand() % 100;

	if(randomtype <=50)
	{
		m_type = dirt;
	}
	else if(randomtype>50&& randomtype <=80)
	{
		m_type = grass;
	}
	else if(randomtype>80)
	{
		m_type = crater;
	}
	if(randomtype>90)
	{
		SetBlocked(true);
	}
	else
	{
		SetBlocked(false);
	}

	m_activeSprite = m_sprites[m_type];
	
}

Tile::~Tile()
{
	for( auto s:m_sprites)
	{
		m_spriteManager->DeleteSprite(s);
		s = nullptr;
	}
	m_spriteManager = nullptr;
	m_drawManager = nullptr;
	
}

SDL_Rect* Tile::GetRect()
{
	return &m_rect;
}

void Tile::Draw(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	m_drawManager->Draw(m_activeSprite, m_x, m_y, 1);


	m_drawManager->DrawRect(m_rect, p_r, p_g, p_b, p_a);
	if(m_blocked)
	{
		m_drawManager->Draw(m_sprites[3], m_x, m_y, 1);
	}

}



void Tile::Update(float p_delta)
{
		
}


Vector2<int> Tile::GetWorldPos()
{
	return Vector2<int>(m_x, m_y);
}

Vector2<int> Tile::GetGridPos()
{
	if (this) {
		return Vector2<int>(m_gridX, m_gridY);
	}
	return Vector2<int>();
}



void Tile::OnClick(std::string p_selectedSpawnType)
{
	if(p_selectedSpawnType=="Dirt")
	{
		m_type = dirt;
		m_activeSprite = m_sprites[0];
		m_blocked = false;

	}
	else if(p_selectedSpawnType=="Grass")
	{
		m_type = grass;
		m_activeSprite = m_sprites[1];
		m_blocked = false;
		
	}
	else if (p_selectedSpawnType == "Crater")
	{
		m_type = crater;
		m_activeSprite = m_sprites[2];
		m_blocked = false;

	}
	
}

bool Tile::IsBlocked()
{
	return m_blocked;
}

void Tile::SetBlocked(bool p_val)
{
	m_blocked = p_val;
}





