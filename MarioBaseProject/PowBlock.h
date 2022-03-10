#pragma once
#include "SDL.h"
#include "LevelMap.h"
#include "Collisions.h"
#include "Texture2D.h"
#ifndef _POWBLOCK_H

class PowBlock
{
public:
	PowBlock(SDL_Renderer* LevelMap);
	~PowBlock();
	void Render();
	Rect2D GetColisionBox() { m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_h; }
	void TakeHit();
	bool IsAvailable() {return m_num_hits_left > 0;}

private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;

};

#endif
