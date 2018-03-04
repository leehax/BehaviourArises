#pragma once
#include <vector>
#include "Sprite.h"
#include "Config.h"
#include "Math.h"


class World;
class DrawManager;
class SpriteManager;

enum Type{Unused= ' ', Wall = '#', Floor = '.'};

class Tile 
{
public:
	Tile(int p_x,  int p_y,  int p_w,  int p_h, int p_gridX, int p_gridY);
	~Tile();
	SDL_Rect* GetRect();
	void Draw(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a);
	void Update(float p_delta);
	Vector2<int> GetWorldPos();
	Vector2<int> GetGridPos();
	void OnClick(std::string p_selectedSpawnType);
	void SetType(const char p_type);
	bool IsBlocked(); 
	void SetBlocked(bool p_val);
	Type m_type;
private:
	
	Type m_previousType;
	bool m_blocked;
	SDL_Rect m_rect;
	DrawManager* m_drawManager;
	SpriteManager* m_spriteManager;
	Sprite* m_activeSprite;
	std::vector<Sprite*> m_sprites;
	unsigned int m_gridX, m_gridY, m_x, m_y;;


};

