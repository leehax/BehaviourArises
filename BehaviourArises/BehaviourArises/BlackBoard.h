#pragma once
#include <map>
#include "Math.h"
class BlackBoard
{
public:
	BlackBoard();
	~BlackBoard();


	void AddInt(std::string p_key, int p_value);
	bool HasInt(std::string p_key) const;
	int GetInt(std::string p_key);
	
	void AddFloat(std::string p_key, float p_value);
	bool HasFloat(std::string p_key) const;
	float GetFloat(std::string p_key);

	void AddString(std::string p_key, std::string p_value);
	bool HasString(std::string p_key) const;
	std::string GetString(std::string p_key);

	void AddBool(std::string p_key, bool p_value);
	bool HasBool(std::string p_key) const;
	bool GetBool(std::string p_key);

	void AddVector2i(std::string p_key, Vector2<int> p_value);
	bool HasVector2i(std::string p_key) const;
	Vector2<int> GetVector2i(std::string p_key);

	void AddVector2f(std::string p_key, Vector2<float> p_value);
	bool HasVector2f(std::string p_key) const;
	Vector2<float> GetVector2f(std::string p_key);

private:
	std::map<std::string, int> m_integers;
	std::map<std::string, float> m_floats;
	std::map<std::string, std::string> m_strings;
	std::map<std::string, bool> m_booleans;
	std::map<std::string, Vector2<int>> m_vector2is;
	std::map<std::string, Vector2<float>> m_vector2fs;

};
