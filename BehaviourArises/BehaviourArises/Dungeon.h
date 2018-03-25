#pragma once
#include "IGridMap.h"
#include <random>
#include <memory>
#include "Healer.h"
#include "Tank.h"
#include "EnemyMob.h"
#include "Mage.h"



class Dungeon :
	public IGridMap
{
public:
	Dungeon();
	~Dungeon();
	void Initialise() override;
	void DrawGrid(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a) override;
	void Update(float p_delta) override;
	void HandleEvent(SDL_Event& p_ev, SDL_Point p_pos) override;
	bool CheckCollisions(std::weak_ptr<Agent> p_first, std::weak_ptr<Agent> p_second);
	bool CheckSensingCollisions(std::weak_ptr<Agent> p_first, std::weak_ptr<Agent> p_second);
	std::weak_ptr<EnemyMob> ClosestEnemy(Vector2<int> p_curPos);
	void SpawnEnemy();
	
private:
	unsigned int m_columns, m_rows, m_tileSize;
	bool LoadMap(std::string p_file);
	std::shared_ptr<Healer> m_healer;
	std::shared_ptr<Tank> m_tank;
	std::shared_ptr<Mage> m_mage;
	std::shared_ptr<BlackBoard> m_worldBlackBoard;
	std::vector<std::shared_ptr<EnemyMob>> m_enemies;
	std::vector<Tile*> m_enemySpawnPositions;
	float m_enemySpawnTimer = 3.f;
	int m_maxEnemies = 10;
};

