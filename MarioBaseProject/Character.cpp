#include "Character.h"
#include "Texture2D.h"
using namespace std;


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
{
	m_moving_left = false;
	m_moving_right = false;
	m_facing_direction = FACING_RIGHT;
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load texture!" << endl;
	}
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
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

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= MOVEMENTSPEED*deltaTime;
}

void Character::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += MOVEMENTSPEED*deltaTime;
}
