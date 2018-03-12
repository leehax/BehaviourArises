#include "stdafx.h"
#include "BlackBoard.h"
#include <iostream>


BlackBoard::BlackBoard()
{
}


BlackBoard::~BlackBoard()
{
}

void BlackBoard::AddInt(std::string p_key, int p_value)
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

void BlackBoard::AddFloat(std::string p_key, float p_value)
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

void BlackBoard::AddString(std::string p_key, std::string p_value)
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

void BlackBoard::AddBool(std::string p_key, bool p_value)
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

void BlackBoard::AddVector2i(std::string p_key, Vector2<int> p_value)
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

void BlackBoard::AddVector2f(std::string p_key, Vector2<float> p_value)
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

void BlackBoard::AddAgent(std::string p_key, Agent* p_agent)
{
	m_agents[p_key] = p_agent;
}

bool BlackBoard::HasAgent(std::string p_key) const
{
	return m_agents.find(p_key) != m_agents.end();
}

Agent* BlackBoard::GetAgent(std::string p_key)
{
	if(!HasAgent(p_key))
	{
		std::cout << "Agent with key " << p_key.c_str() << " not found, returning null";
		return nullptr;
	}

	return m_agents[p_key];
}
