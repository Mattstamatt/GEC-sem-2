#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"

class Texture2D;
class CharacterMario;
class CharacterLuigi;

class GameScreenLevel1 : GameScreen
{

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	CharacterMario* mario_character;
	CharacterLuigi* luigi_character;
	void SetLevelMap();
	LevelMap* m_level_map;
};

#endif // _GAMESCREENLEVEL1_H