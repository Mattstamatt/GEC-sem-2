#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;
	my_character = nullptr;
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	//Draw Mario
	my_character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//update character 
	my_character->Update(deltaTime, e);
}

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		cout << "Failed to load backdround texture!" << endl;
		return false;
	}

	//set up player character
	my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 330));
}
