#include "GameScreenMenu.h"
#include "Texture2D.h"
#include "constants.h"
#include <iostream>
using namespace std;

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpMenuScreen();
}

GameScreenMenu::~GameScreenMenu()
{
	m_background_texture = nullptr;
}

void GameScreenMenu::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
}

bool GameScreenMenu::SetUpMenuScreen()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Mario_Title.png"))
	{
		cout << "Failed to load backdround texture!" << endl;
		return false;
	}

	m_background_yPos = 0;
}

