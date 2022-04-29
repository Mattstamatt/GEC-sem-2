#pragma once
#include "Character.h"
#ifndef _KOOPACHARACHTER_H

class KoopaCharacter : public Character
{
public:
	KoopaCharacter(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~KoopaCharacter();
	void TakeDamage();
	void Jump();
	virtual void KoopaUpdate(float deltaTime, SDL_Event e);
	virtual void Render();
	bool GetInjured() { return m_injured; }

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	float m_movement_speed;
	void FlipRightWayUp();
};

#endif // KoopaCharacter
