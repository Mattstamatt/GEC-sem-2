#pragma once
#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H
#include "GameScreen.h"
#include "Commons.h"
#include <vector>

class Texture2D;

class GameScreenMenu: GameScreen
{
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render() override;

private:
	Texture2D* m_background_texture;
	bool SetUpMenuScreen();
	float m_background_yPos;
};

#endif //_GAMESCREENMENU_H
