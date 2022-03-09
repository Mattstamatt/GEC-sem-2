#pragma once
#include "Character.h"
#ifndef _CHARACTERMARIO_H

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~CharacterMario();
	virtual void MarioUpdate(float deltaTime, SDL_Event e);
};

#endif // _CHARACTERMARIO_H