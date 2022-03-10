#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include <iostream>
using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;
	mario_character = nullptr;
	luigi_character = nullptr;
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	//Draw Mario
	mario_character->Render();
	//Draw Luigi
	luigi_character->LRender();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//update character 
	mario_character->MarioUpdate(deltaTime, e);
	luigi_character->LuigiUpdate(deltaTime, e);

	if (Collisions::Instance()->Circle(mario_character, luigi_character))
	{
		cout << "Circle hit!" << endl;
	}
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
	mario_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330));
	luigi_character = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330));
}
