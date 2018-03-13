#pragma once
#include <map>
#include "Math.h"
#include <memory>
#include "Agent.h"

class BlackBoard
{
public:
	BlackBoard();
	~BlackBoard();


	void SetInt(std::string p_key, int p_value);
	bool HasInt(std::string p_key) const;
	int GetInt(std::string p_key);
	
	void SetFloat(std::string p_key, float p_value);
	bool HasFloat(std::string p_key) const;
	float GetFloat(std::string p_key);

	void SetString(std::string p_key, std::string p_value);
	bool HasString(std::string p_key) const;
	std::string GetString(std::string p_key);

	void SetBool(std::string p_key, bool p_value);
	bool HasBool(std::string p_key) const;
	bool GetBool(std::string p_key);

	void SetVector2i(std::string p_key, Vector2<int> p_value);
	bool HasVector2i(std::string p_key) const;
	Vector2<int> GetVector2i(std::string p_key);

	void SetVector2f(std::string p_key, Vector2<float> p_value);
	bool HasVector2f(std::string p_key) const;
	Vector2<float> GetVector2f(std::string p_key);

	void SetAgent(std::string p_key,Agent* p_agent);
	bool HasAgent(std::string p_key) const;
	Agent* GetAgent(std::string p_key);
	
	void SetTile(std::string p_key, Tile* p_tile);
	bool HasTile(std::string p_key) const;
	Tile* GetTile(std::string p_key);

private:
	std::map<std::string, int> m_integers;
	std::map<std::string, float> m_floats;
	std::map<std::string, std::string> m_strings;
	std::map<std::string, bool> m_booleans;
	std::map<std::string, Vector2<int>> m_vector2is;
	std::map<std::string, Vector2<float>> m_vector2fs;
	std::map<std::string, Agent*> m_agents;
	std::map<std::string, Tile*> m_tiles;
};

