#include "stdafx.h"
#include "BlackBoard.h"
#include <iostream>


BlackBoard::BlackBoard()
{
}


BlackBoard::~BlackBoard()
{
}

void BlackBoard::SetInt(std::string p_key, int p_value)
{
	m_integers[p_key] = p_value;
}

bool BlackBoard::HasInt(std::string p_key) const
{
	return m_integers.find(p_key) != m_integers.end();
}

int BlackBoard::GetInt(std::string p_key)
{
	if (!HasInt(p_key))
	{
		std::cout << "Integer with key " << p_key.c_str() <<" not found, returning a default value\n";
		return 0;
	}

	return m_integers[p_key];
}

void BlackBoard::SetFloat(std::string p_key, float p_value)
{
	m_floats[p_key] = p_value;
}

bool BlackBoard::HasFloat(std::string p_key) const
{
	return m_floats.find(p_key) != m_floats.end();
}

float BlackBoard::GetFloat(std::string p_key)
{
	if (!HasFloat(p_key))
	{
		std::cout << "Float with key " << p_key.c_str() << " not found, returning a default value\n";
		return 0.0f;
	}

	return m_floats[p_key];
}

void BlackBoard::SetString(std::string p_key, std::string p_value)
{
	m_strings[p_key] = p_value;
}

bool BlackBoard::HasString(std::string p_key) const
{
	return m_strings.find(p_key) != m_strings.end();
}

std::string BlackBoard::GetString(std::string p_key)
{
	if(!HasString(p_key))
	{
		std::cout << "String with key " << p_key.c_str() << " not found, returning a default value\n";
		return "";
	}
	
	return m_strings[p_key];
}

void BlackBoard::SetBool(std::string p_key, bool p_value)
{
	m_booleans[p_key] = p_value;
}

bool BlackBoard::HasBool(std::string p_key) const
{
	return m_booleans.find(p_key) != m_booleans.end();
}

bool BlackBoard::GetBool(std::string p_key)
{
	if(!HasBool(p_key))
	{
		std::cout << "Boolean with key " << p_key.c_str() << " not found, returning a default value\n";
		return false;
	}
	
	return m_booleans[p_key];
}

void BlackBoard::SetVector2i(std::string p_key, Vector2<int> p_value)
{
	m_vector2is[p_key] = p_value;
}

bool BlackBoard::HasVector2i(std::string p_key) const
{
	return m_vector2is.find(p_key) != m_vector2is.end();
}

Vector2<int> BlackBoard::GetVector2i(std::string p_key)
{
	if (!HasVector2i(p_key))
	{
		std::cout << "Vector2i with key " << p_key.c_str() << " not found, returning a default value\n";
		return Vector2<int>(0, 0);
	}

	return m_vector2is[p_key];
}

void BlackBoard::SetVector2f(std::string p_key, Vector2<float> p_value)
{
	m_vector2fs[p_key] = p_value;
}

bool BlackBoard::HasVector2f(std::string p_key) const
{
	return m_vector2fs.find(p_key) != m_vector2fs.end();
}

Vector2<float> BlackBoard::GetVector2f(std::string p_key)
{
	if (!HasVector2f(p_key))
	{
		std::cout << "Vector2f with key " << p_key.c_str() << " not found, returning a default value\n";
		return Vector2<float>(0.0f, 0.0f);
	}

	return m_vector2fs[p_key];
}

void BlackBoard::SetAgent(std::string p_key, std::weak_ptr<Agent> p_agent)
{
	m_agents[p_key] = p_agent;
}

bool BlackBoard::HasAgent(std::string p_key) const
{
	return m_agents.find(p_key) != m_agents.end();
}

std::weak_ptr<Agent> BlackBoard::GetAgent(std::string p_key)
{
	if(!HasAgent(p_key))
	{
		std::cout << "Agent with key " << p_key.c_str() << " not found, returning null\n";
		return std::weak_ptr<Agent>();
	}

	return m_agents[p_key];
}

void BlackBoard::SetTile(std::string p_key, Tile* p_tile)
{
	m_tiles[p_key] = p_tile;
}

bool BlackBoard::HasTile(std::string p_key) const
{
	return m_tiles.find(p_key) != m_tiles.end();
}

Tile* BlackBoard::GetTile(std::string p_key)
{
	if (!HasTile(p_key))
	{
		std::cout << "Tile with key " << p_key.c_str() << " not found, returning null\n";
		return nullptr;
	}

	return m_tiles[p_key];
}

void BlackBoard::SetBTNodes(std::string p_key, std::vector<BT_Node*> p_nodes)
{
	m_BTNodes[p_key] = p_nodes;
}

bool BlackBoard::HasBTNodes(std::string p_key) const
{
	return m_BTNodes.find(p_key) != m_BTNodes.end();
}

std::vector<BT_Node*> BlackBoard::GetBTNodes(std::string p_key)
{
	if(!HasBTNodes(p_key))
	{
		std::cout << "Nodes with key " << p_key.c_str() << " not found, returning null\n";
		return {};
		
	}
	return m_BTNodes[p_key];
}
