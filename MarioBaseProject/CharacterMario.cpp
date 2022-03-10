#include "Character.h"
#include "CharacterMario.h"
#include "Texture2D.h"

#ifndef _CHARACTERMARIO_H

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
}

CharacterMario::~CharacterMario()
{
}

void CharacterMario::MarioUpdate(float deltaTime, SDL_Event e)
{
	// checks the arrow pressed to see what direction the player wants to move mario in 
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case (SDLK_RIGHT):
			m_moving_right = true;
			break;

		case (SDLK_LEFT):
			m_moving_left = true;
			break;

		case (SDLK_UP):
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
		case (SDLK_RIGHT):
			m_moving_right = false;
			break;

		case (SDLK_LEFT):
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

#endif //_CHARACTERMARIO_H