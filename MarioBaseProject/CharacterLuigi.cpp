#include "CharacterLuigi.h"
#include "Character.h"
#ifndef _CHARACTERLUIGI_H

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position)
{
}
CharacterLuigi::~CharacterLuigi()
{
}

void CharacterLuigi::LuigiUpdate(float deltaTime, SDL_Event e)
{
	// checks the arrow pressed to see what direction the player wants to move mario in 
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case (SDLK_d):
			m_moving_right = true;
			break;

		case (SDLK_a):
			m_moving_left = true;
			break;

		case (SDLK_w):
			if (m_can_jump)
			{
				Jump();
			}

			break;

		default:
			break;
		}
	default:
		break;
	}
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case (SDLK_d):
			m_moving_right = false;
			break;

		case (SDLK_a):
			m_moving_left = false;
			break;

		default:
			break;
		}
	default:
		break;
	}
	Character::Update(deltaTime, e);
}

#endif //_CHARACTERLUIGI_H