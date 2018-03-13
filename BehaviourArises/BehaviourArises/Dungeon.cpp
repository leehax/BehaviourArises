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

	//if (!CreateRoom(m_rows / 2, m_columns / 2, static_cast<Direction>(RandomInt(4)), true))
	//{
	//	std::cout << "Failed creating first room\n";
	//	return;
	//}

	//for (int i = 1; i < m_maxFeatures; i++)
	//{
	//	if (!CreateFeature())
	//	{
	//		std::cout << "Failed creating feature, Created " << i << " amount \n";
	//		break;
	//	}
	//}
	LoadMap("../External/map.txt");
	m_healer = std::make_unique<Healer>(this,GetTile(1, 1));
	m_healer->CreateBehaviourTree();
}

void Dungeon::DrawGrid(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{

	for (auto t : m_tiles)
	{
		t.second->Draw(p_r, p_g, p_b, p_a);
	}
	m_healer->Draw();
}

void Dungeon::Update(float p_delta)
{
	for (auto t : m_tiles)
	{

		t.second->Update(p_delta);

	}
	m_healer->Update(p_delta);
}


void Dungeon::HandleEvent(SDL_Event& p_ev, SDL_Point p_pos)
{
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
				if(GetTile(x,y))
					GetTile(x, y)->SetType(type);
			}
		}
	}
	return true;
}

bool Dungeon::CreateRoom(int p_x, int p_y, Direction p_dir, bool isFirstRoom)
{
	Rect room;
	room.m_width = RandomInt(m_minRoomSize, m_maxRoomSize);
	room.m_height = RandomInt(m_minRoomSize, m_maxRoomSize);

	switch (p_dir)
	{
	case North:
		room.m_x = p_x - room.m_width / 2;
		room.m_y = p_y - room.m_height;
		break;

	case South:
		room.m_x = p_x - room.m_width / 2;
		room.m_y = p_y + 1;
		break;
	case West:
		room.m_x = p_x - room.m_width;
		room.m_y = p_y - room.m_height / 2;
		break;

	case East:
		room.m_x = p_x + 1;
		room.m_y = p_y - room.m_height / 2;
		break;
	}

	if(FillRect(room,Floor))
	{
		m_rooms.push_back(room);

		if(p_dir != South || isFirstRoom)
		{
			m_exits.push_back(Rect{ room.m_x, room.m_y - 1, room.m_width, 1 });
		}
		if (p_dir != North || isFirstRoom)
		{
			m_exits.push_back(Rect{ room.m_x, room.m_y + room.m_height, room.m_width, 1 });
		}
		if (p_dir != South || isFirstRoom)
		{
			m_exits.push_back(Rect{ room.m_x - 1, room.m_y, 1, room.m_height });
		}
		if (p_dir != South || isFirstRoom)
		{
			m_exits.push_back(Rect{ room.m_x + room.m_width, room.m_y, 1, room.m_height });
		}
		return true;
	}

	return false;
}

bool Dungeon::CreateCorridor(int p_x, int p_y, Direction p_dir)
{

	Rect corridor;
	corridor.m_x = p_x;
	corridor.m_y = p_y;

	if (RandomBool())
	{
		corridor.m_width = RandomInt(m_minRoomSize, m_maxRoomSize);
		corridor.m_height = 1;
		
		switch(p_dir)
		{
		case North:
			corridor.m_y = p_y - 1;
			if(RandomBool())
			{
				corridor.m_x = p_x - corridor.m_width + 1;
			}
			break;
		case South:
			corridor.m_y = p_y + 1;
			if (RandomBool())
			{
				corridor.m_x = p_x - corridor.m_width + 1;
			}
			break;
		case West:
			corridor.m_x = p_x - corridor.m_width;
			break;
		case East:
			corridor.m_x = p_x + 1;
			break;
		}
	}
	else
	{
		corridor.m_width = 1;
		corridor.m_height = RandomInt(m_minRoomSize, m_maxRoomSize);

		switch (p_dir)
		{
		case North:
			corridor.m_y = p_y - corridor.m_height;
			break;
		case South:
			corridor.m_y = p_y + 1;
			break;
		case West:
			corridor.m_x = p_x - 1;
			if (RandomBool())
			{
				corridor.m_y = p_y - corridor.m_height + 1;
			}
			break;
		case East:
			corridor.m_x = p_x + 1;
			if (RandomBool())
			{
				corridor.m_y = p_y - corridor.m_height + 1;
			}
			break;
		}
	
	}
	if(FillRect(corridor,Floor))
	{

		if (p_dir != South && corridor.m_width != 1) 
			m_exits.push_back(Rect{ corridor.m_x, corridor.m_y - 1, corridor.m_width, 1 });
		if (p_dir != North && corridor.m_width != 1)
			m_exits.push_back(Rect{ corridor.m_x, corridor.m_y + corridor.m_height, corridor.m_width, 1 });
		if (p_dir != East && corridor.m_height != 1) 
			m_exits.push_back(Rect{ corridor.m_x - 1, corridor.m_y, 1, corridor.m_height });
		if (p_dir != West && corridor.m_height != 1) 
			m_exits.push_back(Rect{ corridor.m_x + corridor.m_width, corridor.m_y, 1, corridor.m_height });
		return true;
	}
	return false;
}

bool Dungeon::CreateFeature()
{
	for (int i = 0; i < 1000; i++)
	{
		if (m_exits.empty())
		{
			break;
		}

		int a = RandomInt(m_exits.size());
		int x = RandomInt(m_exits[a].m_x, m_exits[a].m_x + m_exits[a].m_width - 1);
		int y = RandomInt(m_exits[a].m_y, m_exits[a].m_y + m_exits[a].m_height - 1);

		for(int j = 0; j < 4; j++)
		{
			if(CreateFeature(x ,y ,static_cast<Direction>(j)))
			{
				m_exits.erase(m_exits.begin() + a);
				return true;
			}
		}
	}
	return false;
}

bool Dungeon::CreateFeature(int p_x, int p_y, Direction p_dir)
{
	static const int roomChance = 60;

	int dx =0, dy = 0;

	switch (p_dir)
	{
	case North:
		dy = 1;
		break;
	case South: 
		dy = -1;
		break;
	case West:
		dx = 1;
		break;
	case East: 
		dx = -1;
		break;
	}
	if (GetTile(p_x + dx, p_y + dy))
	{
		if (GetTile(p_x + dx, p_y + dy)->m_type != Floor)
		{
			return false;
		}
	}
	if(RandomInt(100)<roomChance)
	{
		if (CreateRoom(p_x,p_y,p_dir,false))
		{
			GetTile(p_x, p_y)->SetType(Floor);
			return true;
		}
	}
	else
	{
		if(CreateCorridor(p_x,p_y,p_dir))
		{
			if(GetTile(p_x+dx,p_y+dy)->m_type==Floor)
			{
				GetTile(p_x, p_y)->SetType(Floor);
			}
			return true;
		}
	}
	return false;
}

bool Dungeon::FillRect(const Rect& p_rect, const char p_type)
{
	if (p_rect.m_x  < 1 || p_rect.m_x + p_rect.m_width >Config::COLUMNS - 1 || p_rect.m_y < 1 || p_rect.m_y + p_rect.m_height>Config::ROWS - 1)
	{
		return false;
	}

	for (int y = p_rect.m_y; y < p_rect.m_y + p_rect.m_height; y++)
	{
		for (int x = p_rect.m_x; x < p_rect.m_x + p_rect.m_width; x++)
		{
			if (GetTile(x, y)->m_type != Unused)
				return false;
		}
		
	}

	for (int y = p_rect.m_y - 1; y < p_rect.m_y + p_rect.m_height + 1; y++)
	{
		for (int x = p_rect.m_x - 1; x < p_rect.m_x + p_rect.m_width + 1; x++)
		{
			if (x == p_rect.m_x - 1 || x == p_rect.m_x + p_rect.m_width ||
				y == p_rect.m_y - 1 || y == p_rect.m_y + p_rect.m_height)
			{
				GetTile(x, y)->SetType(Wall);
			}
			else
			{
				GetTile(x, y)->SetType(p_type);
			}
		}

	}
	return true;
}


