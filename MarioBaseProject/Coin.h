#pragma once
#include "SDL.h"
#include "LevelMap.h"
#include "Collisions.h"
#include "Texture2D.h"
#ifndef _COIN_H

class Coin
{
public:
	Coin(SDL_Renderer* renderer);
	~Coin();
	void Render();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_h); }
	void CoinSpin();
	void CoinPickup();
	bool IsAvailable() { return !m_collected; }

private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_spin_portion;
	bool m_collected;
	float m_spin_speed;
	Coin* m_coin;
};

#endif // !_COIN_H
