#pragma once
#include <string>
#include <vector>
#include <memory>


class DrawManager;
class SpriteManager;
class Sprite;
class GuiButton
{
public:
	GuiButton(int p_x, int p_y, std::string p_name, std::string p_spriteFilePath);
	GuiButton(int p_x, int p_y, std::string p_name);
	~GuiButton();
	void Draw();
	void SetActive(bool p_val);
	void HandleButtonEvent(SDL_MouseButtonEvent p_mEv);
	bool IsActive();
	SDL_Rect* GetRect();
	std::string GetName();
private:

	
	DrawManager * m_drawManager;
	SpriteManager* m_spriteManager;
	Sprite* m_sprite;
	SDL_Rect m_rect;
	std::string m_name;
	SDL_Color m_color1;
	SDL_Color m_color2;
	SDL_Color m_activeColor;
	bool m_active;
	int m_textYOffset, m_textXOffset;

};

