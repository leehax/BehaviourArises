#include "stdafx.h"
#include "Spaceship.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "Tile.h"
#include "ServiceLocator.h"
Spaceship::Spaceship()
{
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite("../External/textures/Spaceship.png", 0, 0, 32, 32);
	m_type = "Ship";
}


Spaceship::~Spaceship()
{
	m_spriteManager->DeleteSprite(m_sprite);
	m_sprite = nullptr;
	m_spriteManager = nullptr;
	m_drawManager = nullptr;
}

void Spaceship::Update(float p_delta)
{
}

void Spaceship::Draw()
{
	m_drawManager->Draw(m_sprite, GetWorldPos().x, GetWorldPos().y, 1);
}
