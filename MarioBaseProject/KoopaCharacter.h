#pragma once
#include "Character.h"
#ifndef KOOPACHARACHTER

class KoopaCharacter : public Character
{
public:
	KoopaCharacter(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~KoopaCharacter();
	void TakeDamage();
	void Jump();
	virtual void KUpdate(float deltaTime, SDL_Event e);
	virtual void KRender();
	bool GetInjured() { return m_injured; }

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	float m_movement_speed;
	Vector2D m_position;
	void FlipRightWayUp();


};

#endif // KoopaCharacter
