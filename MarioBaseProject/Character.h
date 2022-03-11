#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "LevelMap.h"

#ifndef _CHARACTER_H
using namespace std;

class Texture2D;

class Character
{

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();
	virtual void Render();
	virtual void LRender();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
	float GetCollisionRadius();
	void AddGravity(float deltaTime);
	void Jump();
	bool IsJumping() { return false; }
	void CancelJump() { return; }

	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());}

protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	FACING m_facing_direction;
	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	float m_collision_radius;
	LevelMap* m_current_level_map;

};

#endif //_CHARACTER_H