#include "PowBlock.h"
#include <iostream>
using namespace std;
PowBlock::PowBlock(SDL_Renderer* LevelMap)
{
	string imagePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture." << endl;
	}
	
}
