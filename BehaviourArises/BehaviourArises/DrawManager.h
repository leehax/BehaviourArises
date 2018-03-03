#pragma once
#include "Sprite.h"
#include <string>


class DrawManager
{
public:
	DrawManager();
	~DrawManager();

	void Initialise();
	void Destroy();
	void Clear();
	void Present();
	void Draw(Sprite* p_sprite, int p_x, int p_y, int p_scale);
	void DrawRect(SDL_Rect& p_rect, Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a);
	void DrawLine(int p_xPos, int p_yPos, int p_xTarget, int p_yTarget, Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a);
	void DrawText(int p_xPos, int p_Ypos, std::string p_text, SDL_Color p_color);

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();
	TTF_Font* GetDefFont();
private:

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	TTF_Font* m_defaultFont;
	bool LoadFont(const int p_size);
	void UnloadFont();



};

