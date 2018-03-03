#pragma once
class Sprite
{
public:
	Sprite(SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h);
	~Sprite();
	void SetClip(int p_x, int p_y, int p_w, int p_h);
	SDL_Rect GetClip();
	SDL_Texture* GetTexture();
private:
	SDL_Texture* m_tex;
	SDL_Rect m_clip;

};

