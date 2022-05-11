#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "CharacterMario.h"
#include "KoopaCharacter.h"
#include "LevelMap.h"
#include <vector>

class Texture2D;
class CharacterMario;
class KoopaCharacter;
class PowBlock;
class Coin;

class GameScreenLevel1 : GameScreen
{

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
	void UpdateCoin();

private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	CharacterMario* mario_character;
	KoopaCharacter* Koopa;
	void SetLevelMap();
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	Coin* m_coin;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	void DoScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	vector<KoopaCharacter*> m_enemies;
};

#endif // _GAMESCREENLEVEL1_H