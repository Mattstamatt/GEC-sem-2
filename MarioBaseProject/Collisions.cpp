#include "Collisions.h"
#include "Character.h"

//iniialise instance to nullptr
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	m_instance = nullptr
}

Collisions* Collisions::Instance()
{
	if (!m_instance)
	{
		m_instance = new Collisions;
	}
	return nullptr;
}

bool Collisions::Circle(Character* character1, Character* character2)
{
	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x),
		(character1->GetPosition().y - character2->GetPosition().y));
}
