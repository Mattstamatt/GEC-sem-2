#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "constants.h"
#include "PowBlock.h"
#include "Coin.h"
#include <iostream>
using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;
	mario_character = nullptr;
	delete m_pow_block;
	m_pow_block = nullptr;
	delete m_coin;
	m_coin = nullptr;
	m_enemies.clear();
}

void GameScreenLevel1::Render()
{
	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	//Draw Mario
	mario_character->MRender();
	//call PowBlocks render function
	m_pow_block->Render();
	//draw the coin
	m_coin->Render();
	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	/*
		do the screen shake if required	
	*/
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_screenshake = false;
			m_background_yPos = 0.0f;
		}
	}

	//update character 
	mario_character->MarioUpdate(deltaTime, e);

	UpdatePOWBlock();
	UpdateCoin();
	UpdateEnemies(deltaTime, e);
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (mario_character->IsJumping() && m_screenshake == false)
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario_character->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::UpdateCoin()
{
	if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), m_coin->GetCollisionBox()))
	{
		if (m_coin->IsAvailable())
		{
			m_coin->CoinPickup();
		}
	}
	m_coin->CoinSpin();
}

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load backdround texture!" << endl;
		return false;
	}

	SetLevelMap();
	//set up player character
	mario_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_RIGHT, KOOPA_SPEED);
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_coin = new Coin(m_renderer);
	m_screenshake = false;
	m_background_yPos = 0.0f;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };


	//clear any old maps 
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	//set the new one 
	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles 
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off the screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55))
					m_enemies[i]->SetAlive(false);
			}
			//now do the update 
			m_enemies[i]->KoopaUpdate(deltaTime, e);

			//check to see if enemy collides with player 
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe 
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], mario_character))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//kill mario
						mario_character->SetAlive(false);
					}
				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}

	}


}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	m_enemies.push_back(new KoopaCharacter(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed));
}

