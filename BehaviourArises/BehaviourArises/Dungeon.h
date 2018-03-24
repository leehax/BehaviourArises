#pragma once
#include "IGridMap.h"
#include <random>
#include <memory>
#include "Healer.h"
#include "Tank.h"
#include "EnemyMob.h"
#include "Ranger.h"


struct Rect
{
	int m_x, m_y;
	int m_width, m_height;

};

class Dungeon :
	public IGridMap
{
public:
	enum Direction{ North, South, West, East };
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
//	bool EntityOnTile(Tile* p_tile);
	//Tile* GetTileWithEntity(const std::string p_type);
		

private:
	unsigned int m_columns, m_rows, m_tileSize;
	unsigned int m_minRoomSize = 3;
	unsigned int m_maxRoomSize = 6;
	unsigned int m_maxFeatures = 10;
	bool LoadMap(std::string p_file);

	bool CreateRoom(int p_x, int p_y, Direction p_dir, bool isFirstRoom);
	bool CreateCorridor(int p_x, int p_y, Direction p_dir);
	bool CreateFeature();
	bool CreateFeature(int p_x, int p_y, Direction p_dir);
	
	bool FillRect(const Rect& p_rect, const char p_type);
	std::vector<Rect> m_rooms;
	std::vector<Rect> m_exits;
	std::shared_ptr<Healer> m_healer;
	std::shared_ptr<Tank> m_tank;
	std::shared_ptr<Ranger> m_ranger;
	std::shared_ptr<BlackBoard> m_worldBlackBoard;
	std::vector<std::shared_ptr<EnemyMob>> m_enemies;

	std::vector<Tile*> m_enemySpawnPositions;
	float m_enemySpawnTimer = 3.f;
	int m_maxEnemies = 10;
};

