#include "Coin.h"
#include <iostream>
using namespace std;

Coin::Coin(SDL_Renderer* renderer)
{
	string imagePath = "Images/Coin.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture." << endl;
		return;
	}

	m_single_sprite_w = m_texture->GetWidth() / 3; // there are three images of this sprite sheet in a row 
	m_single_sprite_h = m_texture->GetHeight();
	m_spin_portion = 3;
	m_spin_speed = 0;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5f, 100);
	m_collected = false;
}

Coin::~Coin()
{
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
	m_level_map = nullptr;
}

void Coin::CoinSpin()
{
	if (!m_collected)
	{ 
		m_spin_speed += COINSPINSPEED;

		if (m_spin_speed >= 1)
		{
			m_spin_portion -= 1;
			m_spin_speed = 0;
		}

		if (m_spin_portion <= 0)
		{
			m_spin_portion = 3;
		}
	}

	else
	{
		m_spin_portion = 0;
	}
}

void Coin::CoinPickup()
{
	m_collected = true;
}

void Coin::Render()
{
	if (!m_collected)
	{
		//get the portion of the sheet we want to draw
		int left = m_single_sprite_w * (m_spin_portion - 1);

		//xPos, yPos, sprite sheet width, sprite sheet height
		SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

		//determine where to draw it
		SDL_Rect dest_rect = { static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_single_sprite_w, m_single_sprite_h };

		//draw the sprite
		m_texture->Render(portion_of_sprite, dest_rect, SDL_FLIP_NONE);
	}
}

