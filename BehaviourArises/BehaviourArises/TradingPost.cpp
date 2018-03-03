#include "stdafx.h"
#include "TradingPost.h"
#include "Tile.h"
#include "ServiceLocator.h"
#include "DrawManager.h"
#include "SpriteManager.h"
TradingPost::TradingPost()
{
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite("../External/textures/Trader.png", 0, 0, 32, 32);
	m_type = "TrPost";
}


TradingPost::~TradingPost()
{
	m_spriteManager->DeleteSprite(m_sprite);
	m_sprite = nullptr;
	m_spriteManager = nullptr;
	m_drawManager = nullptr;
}

void TradingPost::Update(float p_delta)
{
}

void TradingPost::Draw()
{
	m_drawManager->Draw(m_sprite, GetWorldPos().x, GetWorldPos().y, 1);
}

