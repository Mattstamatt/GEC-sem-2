#include "KoopaCharacter.h"

KoopaCharacter::KoopaCharacter(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) :
	Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

KoopaCharacter::~KoopaCharacter()
{
}

void KoopaCharacter::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}

void KoopaCharacter::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

void KoopaCharacter::KoopaUpdate(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (!m_injured)
	{
		//enemy is not injured so move 
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_left = false;
			m_moving_right = true;
		}
	}
	else
	{
		//we shouldnt move if injured
		m_moving_right = false;
		m_moving_left = false;

		//count down injured time
		m_injured_time -= deltaTime;
		if (m_injured_time <= 0.0)
		{
			FlipRightWayUp();
		}
	}
}

void KoopaCharacter::KoopaRender()
{
	//variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	//if injured move the left position of the second image of the sprite sheet 
	if (m_injured)
	{
		left = m_single_sprite_w;
	}

	//get the portion of the sprite sheet you want to draw 
	//{xPos, yPos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite{ left, 0, m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//then draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void KoopaCharacter::FlipRightWayUp()
{
	m_facing_direction = FACING_LEFT;
	m_injured = false;
}
