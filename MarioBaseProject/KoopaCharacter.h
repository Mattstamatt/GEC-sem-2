#pragma once
#include "Character.h"
#ifndef KOOPACHARACHTER

class KoopaCharacter : public Character
{
public:
	void TakeDamage();
	void Jump();
	virtual void KoopaUpdate();
	virtual void KoopaRender();

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	void FlipRightWayUp();


};

#endif // KoopaCharacter
