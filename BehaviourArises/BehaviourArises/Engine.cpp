#include "stdafx.h"
#include "Engine.h"
#include <iostream>
#include "IGridMap.h"
#include "ServiceLocator.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "Dungeon.h"

Engine::Engine()
{
	assert(SDL_Init(SDL_INIT_EVERYTHING) == 0 && "SDL_Init FAILED!"); //SDL_Init returns 0 on success

	assert(IMG_Init(IMG_INIT_PNG) ==IMG_INIT_PNG && "IMG_Init FAILED!"); //IMG_Init returns the flag on success

	assert(TTF_Init() == 0 && "TTF_Init FAILED!");	//TTF_Init returns 0 on success

}


Engine::~Engine()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Engine::Initialise()
{
	m_drawManager = new DrawManager();
	m_world = new Dungeon();
	m_drawManager->Initialise();
	m_spriteManager = new SpriteManager(m_drawManager->GetRenderer());
	

	ServiceLocator<DrawManager>::ProvideService(m_drawManager);
	ServiceLocator<SpriteManager>::ProvideService(m_spriteManager);
	m_world->Initialise();
	isRunning = true;
}

void Engine::Destroy()
{

	delete m_world;
	m_world = nullptr;

	delete m_spriteManager;
	m_spriteManager = nullptr;

	m_drawManager->Destroy();
	delete m_drawManager;
	m_drawManager = nullptr;

}

void Engine::Run()
{

	while(isRunning)
	{
		m_drawManager->Clear();
		CalculateDelta();
		HandleEvents();
		
		m_world->Update(m_delta);
		m_world->DrawGrid(0, 0, 0, 255);
		m_drawManager->Present();
	}
}

void Engine::CalculateDelta()
{
	m_delta = 0.001f*(SDL_GetTicks() - m_lastTick);
	m_lastTick = SDL_GetTicks();
}

void Engine::HandleEvents()
{
	SDL_Event event;
	SDL_Point mousePos;

	while (SDL_PollEvent(&event) == 1)
	{
		SDL_GetMouseState(&mousePos.x, &mousePos.y);

		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		else
		{
			m_world->HandleEvent(event, mousePos);
		}
	}
}

