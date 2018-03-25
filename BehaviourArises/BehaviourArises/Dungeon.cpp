#include "stdafx.h"
#include "Dungeon.h"
#include <iostream>
#include <fstream>
#include "Tile.h"
#include "BehaviourTree.h"
#include "BT_Node.h"
#include "BT_Leaf.h"
#include "BT_Composites.h"
#include "BT_Decorators.h"
#include <ctime>


Dungeon::Dungeon()
{

	m_rows = Config::ROWS;
	m_columns = Config::COLUMNS;
	m_tileSize = Config::TILE_SIZE;
}


Dungeon::~Dungeon()
{
}

void Dungeon::Initialise()
{

	for (unsigned int x = 0; x < m_columns; x++)
	{
		for (unsigned int y = 0; y < m_rows; y++)
		{
			Tile* tile = new Tile(x*m_tileSize, y*m_tileSize, m_tileSize, m_tileSize, x, y);
			tile->SetType(' ');
			m_tiles[std::make_pair(x, y)] = tile;

		}
	}

	LoadMap("../External/map.txt");
	m_worldBlackBoard = std::make_shared<BlackBoard>();


	m_healer = std::make_shared<Healer>(this,GetTile(1, 1), m_worldBlackBoard);
	
	m_healer->CreateBehaviourTree(m_healer);

	m_tank = std::make_shared<Tank>(this, GetTile(15, 3), m_worldBlackBoard);
	m_tank->CreateBehaviourTree(m_tank);

	m_mage = std::make_shared<Mage>(this, GetTile(4, 4), m_worldBlackBoard);
	m_mage->CreateBehaviourTree(m_mage);


	m_worldBlackBoard->SetAgent("Tank", m_tank);
	m_worldBlackBoard->SetAgent("Healer", m_healer);
	m_worldBlackBoard->SetAgent("Mage", m_mage);

	m_enemySpawnPositions.push_back(GetTile(11, 0));
	m_enemySpawnPositions.push_back(GetTile(12, 0));
	m_enemySpawnPositions.push_back(GetTile(0, 11));
	m_enemySpawnPositions.push_back(GetTile(0, 12));
	m_enemySpawnPositions.push_back(GetTile(23, 11));
	m_enemySpawnPositions.push_back(GetTile(23, 12));
	m_enemySpawnPositions.push_back(GetTile(11, 23));
	m_enemySpawnPositions.push_back(GetTile(12, 23));
	for(auto s:m_enemySpawnPositions)
	{
		s->SetBlocked(true);
	}

	m_enemies.push_back(std::make_unique<EnemyMob>(this, GetTile(1, 4)));
	m_enemies.push_back(std::make_unique<EnemyMob>(this, GetTile(4, 5)));
	m_enemies.push_back(std::make_unique<EnemyMob>(this, GetTile(13, 7)));
	m_enemies.push_back(std::make_unique<EnemyMob>(this, GetTile(18, 17)));

}

void Dungeon::DrawGrid(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{

	for (auto t : m_tiles)
	{
		t.second->Draw(p_r, p_g, p_b, p_a);
	}
	
	for(auto e:m_enemies)
	{
		e->Draw();
	}
	m_healer->Draw();
	if(m_tank)
		m_tank->Draw();
	m_mage->Draw();

}

void Dungeon::Update(float p_delta)
{

	m_enemySpawnTimer -= p_delta;
	if(m_enemySpawnTimer<=0 && m_enemies.size()<=m_maxEnemies)
	{
		SpawnEnemy();
	}
	for (auto t : m_tiles)
	{

		t.second->Update(p_delta);

	}

	for (auto e : m_enemies)
	{
		e->Update(p_delta);
		if (m_healer) {
			CheckCollisions(m_healer, e);
			CheckSensingCollisions(e, m_healer);
		}
		if (m_tank)
		{
			CheckCollisions(m_tank, e);
			CheckSensingCollisions(e, m_tank);
		}
		if (m_mage)
		{
			CheckCollisions(m_mage, e);
			CheckSensingCollisions(e, m_mage);
		}


	}
	
	m_enemies.erase(std::remove_if(m_enemies.begin(),m_enemies.end(),[](std::shared_ptr<EnemyMob> enemy)
	{
		return enemy->GetHealth() <= 0;
	}), m_enemies.end());


	if (m_tank) {

		m_tank->Update(p_delta);
		if (m_tank->GetHealth() <= 0) {
			m_tank->DestroyBehaviorTree();
			m_tank.reset();
		}
	}
	if (m_healer)
	{
		m_healer->Update(p_delta);
		if(m_healer->GetHealth()<=0)
		{
			m_healer->DestroyBehaviorTree();
			m_healer.reset();
		}
	}
	if(m_mage)
	{
		m_mage->Update(p_delta);
		if(m_mage->GetHealth()<=0)
		{
			m_mage->DestroyBehaviorTree();
			m_mage.reset();
		}
	}


}


void Dungeon::HandleEvent(SDL_Event& p_ev, SDL_Point p_pos)
{
}

bool Dungeon::CheckCollisions(std::weak_ptr<Agent> p_first, std::weak_ptr<Agent> p_second)
{
	auto sptrFirst = p_first.lock();
	auto sptrSecond = p_second.lock();

		if (sptrFirst->GetCollider().x + sptrFirst->GetCollider().w <= sptrSecond->GetCollider().x ||
			sptrFirst->GetCollider().x >= sptrSecond->GetCollider().x + sptrSecond->GetCollider().w ||
			sptrFirst->GetCollider().y + sptrFirst->GetCollider().h <= sptrSecond->GetCollider().y ||
			sptrFirst->GetCollider().y >= sptrSecond->GetCollider().y + sptrSecond->GetCollider().h)
		{
			return false;

		}
		else
		{
			sptrFirst->OnCollision(sptrSecond);
			return true;
		}



}

bool Dungeon::CheckSensingCollisions(std::weak_ptr<Agent> p_first, std::weak_ptr<Agent> p_second)
{
	auto sptrFirst = p_first.lock();
	auto sptrSecond = p_second.lock();

		if (sptrFirst->GetSensingAreaCollider().x + sptrFirst->GetSensingAreaCollider().w <= sptrSecond->GetCollider().x ||
			sptrFirst->GetSensingAreaCollider().x >= sptrSecond->GetCollider().x + sptrSecond->GetCollider().w ||
			sptrFirst->GetSensingAreaCollider().y + sptrFirst->GetSensingAreaCollider().h <= sptrSecond->GetCollider().y ||
			sptrFirst->GetSensingAreaCollider().y >= sptrSecond->GetCollider().y + sptrSecond->GetCollider().h)
		{
			return false;
		}
		else
		{
			sptrFirst->OnAgentEnteredSenseArea(sptrSecond);
			return true;
		}

}

std::weak_ptr<EnemyMob> Dungeon::ClosestEnemy(Vector2<int> p_curPos)
{
	int maxDist = INT_MAX;
	int index = -1;

	for(int i=0; i<m_enemies.size();i++)
	{
		int curDist = Manhattan(p_curPos, m_enemies[i]->GetGridPos());
		if (curDist<=maxDist)
		{
			maxDist = curDist;
			index = i;
		}
	}

	if(index>=0)
	{
		return m_enemies[index];
	}

	return std::weak_ptr<EnemyMob>(); //empty weak_ptr
}

void Dungeon::SpawnEnemy()
{
	int rand=RandomInt(m_enemySpawnPositions.size());

	m_enemies.push_back(std::make_unique<EnemyMob>(this, m_enemySpawnPositions[rand]));
	m_enemySpawnTimer = 3.f;
}


bool Dungeon::LoadMap(std::string p_file)
{

	std::ifstream mapFile(p_file, std::ios::in);
	if (!mapFile.is_open()) {
		std::cout << "Failed to open the map file!\n";
		return false;
	}
	else {
		for (int y = 0; y < Config::ROWS; y++)
		{
			for (int x = 0; x < Config::COLUMNS; x++)
			{
				char type;
				mapFile >> type;
			
					if (GetTile(x, y))
						GetTile(x, y)->SetType(type);
				
			}
		}
	}
	return true;
}

