#pragma once
#include "Character.h"
class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();
	virtual void LuigiUpdate(float deltaTime, SDL_Event e);
	virtual void LRender();

};

