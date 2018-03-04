#pragma once
class DrawManager;
class SpriteManager;
class World;
class Dungeon;
class Engine
{
public:
	Engine();
	~Engine();
	void Initialise();
	void Destroy();
	void Run();

private:
	void CalculateDelta();
	void HandleEvents();
	bool isRunning;
	float m_delta;

	int m_frameCount;
	int m_frameRate;
	unsigned int m_lastTick;
	unsigned int m_nextTick;

	DrawManager* m_drawManager;
	SpriteManager* m_spriteManager;
	Dungeon* m_world;


};

